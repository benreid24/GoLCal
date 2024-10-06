#include <MainState.hpp>

#include <Constants.hpp>
#include <DescriptorSet.hpp>
#include <gol/gol.h>

namespace
{} // namespace

const char* MainState::name() const { return "MainState"; }

void MainState::activate(bl::engine::Engine& engine) {
    if (!engine.renderer().pipelineCache().pipelineExists(PipelineId)) {
        VkPipelineDepthStencilStateCreateInfo depthStencil{};
        depthStencil.sType            = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
        depthStencil.depthTestEnable  = VK_FALSE;
        depthStencil.depthWriteEnable = VK_FALSE;
        depthStencil.depthCompareOp   = VK_COMPARE_OP_LESS_OR_EQUAL;
        depthStencil.depthBoundsTestEnable = VK_FALSE;
        depthStencil.minDepthBounds        = 0.0f; // Optional
        depthStencil.maxDepthBounds        = 1.0f; // Optional
        depthStencil.stencilTestEnable     = VK_FALSE;
        depthStencil.front                 = {}; // Optional (Stencil)
        depthStencil.back                  = {}; // Optional (Stencil)

        VkPipelineRasterizationStateCreateInfo rasterizer{};
        rasterizer.sType            = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
        rasterizer.depthClampEnable = VK_FALSE;
        rasterizer.rasterizerDiscardEnable = VK_FALSE;
        rasterizer.polygonMode             = VK_POLYGON_MODE_FILL;
        rasterizer.lineWidth               = 1.0f;
        rasterizer.cullMode                = VK_CULL_MODE_NONE;
        rasterizer.frontFace               = VK_FRONT_FACE_COUNTER_CLOCKWISE;
        rasterizer.depthBiasEnable         = VK_FALSE;
        rasterizer.depthBiasConstantFactor = 0.0f; // Optional
        rasterizer.depthBiasClamp          = 0.0f; // Optional
        rasterizer.depthBiasSlopeFactor    = 0.0f; // Optional

        engine.renderer().pipelineCache().createPipline(
            PipelineId,
            bl::rc::vk::PipelineParameters()
                .withShaders("Resources/Shaders/vertex.vert.spv",
                             "Resources/Shaders/fragment.frag.spv")
                .withPrimitiveType(VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST)
                .withRasterizer(rasterizer)
                .withDepthStencilState(&depthStencil)
                .addDescriptorSet<bl::rc::ds::Scene2DFactory>()
                .addDescriptorSet<bl::rc::ds::Object2DFactory>()
                .addDescriptorSet<Factory>()
                .build());
    }

    auto scene = engine.renderer().getObserver().pushScene<bl::rc::scene::Scene2D>();
    engine.renderer().getObserver().setCamera<bl::cam::Camera2D>(WindowSize * 0.5f, WindowSize);
    engine.renderer().getObserver().setClearColor(bl::sfcol(sf::Color::Cyan));

    grid.create(engine, glm::vec2(Width * CellSize, Height * CellSize));
    grid.getTransform().setOrigin(grid.getSize() * 0.5f);
    grid.getTransform().setPosition(WindowSize * 0.5f);
    grid.setFillColor(sf::Color::Red);
    grid.addToSceneWithCustomPipeline(scene, bl::rc::UpdateSpeed::Dynamic, PipelineId);

    payload           = &scene->getDescriptorSet<Set>().getBindingPayload<ShaderPayload>();
    payload->gridSize = grid.getSize();
    payload->width    = Width;
    payload->height   = Height;

    golInit(Width, Height);
    copyData();
}

void MainState::deactivate(bl::engine::Engine& engine) {
    engine.renderer().getObserver().popScene();
}

void MainState::update(bl::engine::Engine&, float dt, float) {
    residual += dt;
    while (residual >= TickPeriod) {
        residual -= TickPeriod;
        golTick();
        copyData();
    }
}

void MainState::copyData() {
    for (unsigned int x = 0; x < Width; ++x) {
        for (unsigned int y = 0; y < Height; ++y) {
            payload->cells[y * Width + x] = *golFetchPrev(x, y);
        }
    }
}
