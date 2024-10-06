#include <Game.hpp>

#include <DescriptorSet.hpp>
#include <MainState.hpp>
#include <iostream>

namespace
{
// one instance should exist globally
Game game;
} // namespace

bool Game::performEarlyStartup(int argc, char** argv) { return true; }

bl::engine::Settings Game::createStartupParameters() {
    return bl::engine::Settings().fromConfig().withWindowParameters(
        bl::engine::Settings::WindowParameters()
            .withVideoMode(sf::VideoMode(1920, 1080, 32))
            .fromConfig()
            .withStyle(sf::Style::Close | sf::Style::Titlebar | sf::Style::Resize)
            .withTitle("Game of Life Calendar")
            .withLetterBoxOnResize(true)
            .withInitialViewSize(sf::Vector2f(1920.f, 1080.f)));
}

bool Game::completeStartup(bl::engine::Engine& engine) {
    VkPipelineDepthStencilStateCreateInfo depthStencil{};
    depthStencil.sType                 = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
    depthStencil.depthTestEnable       = VK_FALSE;
    depthStencil.depthWriteEnable      = VK_FALSE;
    depthStencil.depthCompareOp        = VK_COMPARE_OP_LESS_OR_EQUAL;
    depthStencil.depthBoundsTestEnable = VK_FALSE;
    depthStencil.minDepthBounds        = 0.0f; // Optional
    depthStencil.maxDepthBounds        = 1.0f; // Optional
    depthStencil.stencilTestEnable     = VK_FALSE;
    depthStencil.front                 = {}; // Optional (Stencil)
    depthStencil.back                  = {}; // Optional (Stencil)

    VkPipelineRasterizationStateCreateInfo rasterizer{};
    rasterizer.sType                   = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    rasterizer.depthClampEnable        = VK_FALSE;
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
            .withShaders("Resources/Shaders/vertex.vert.spv", "Resources/Shaders/fragment.frag.spv")
            .withPrimitiveType(VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST)
            .withRasterizer(rasterizer)
            .withDepthStencilState(&depthStencil)
            .addDescriptorSet<bl::rc::ds::Scene2DFactory>()
            .addDescriptorSet<bl::rc::ds::Object2DFactory>()
            .addDescriptorSet<Factory>()
            .build());

    return true;
}

bl::engine::State::Ptr Game::createInitialEngineState() { return MainState::create(); }

void Game::startShutdown() {}

void Game::completeShutdown() {}
