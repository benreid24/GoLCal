#include <MainState.hpp>

#include <Constants.hpp>
#include <DescriptorSet.hpp>
#include <SFML/Graphics.hpp>
#include <chrono>
#include <gol/gol.h>
#include <iomanip>

namespace
{
std::string now() {
    auto timeNow       = std::chrono::system_clock::now();
    std::time_t time   = std::chrono::system_clock::to_time_t(timeNow);
    std::tm local_time = *std::localtime(&time);
    std::stringstream ss;
    ss << std::put_time(&local_time, "%m/%d\n%Y");
    return ss.str();
}
} // namespace

MainState::MainState()
: State(bl::engine::StateMask::Running)
, residual(0.f)
, paused(false)
, prevClick(std::numeric_limits<unsigned int>::max(), std::numeric_limits<unsigned int>::max()) {}

const char* MainState::name() const { return "MainState"; }

void MainState::activate(bl::engine::Engine& engine) {
    e = &engine;

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
    engine.renderer().getObserver().setClearColor(bl::sfcol(sf::Color::Black));

    grid.create(engine, glm::vec2(Width * CellSize, Height * CellSize));
    grid.getTransform().setOrigin(grid.getSize() * 0.5f);
    grid.getTransform().setPosition(WindowSize * 0.5f);
    grid.setFillColor(sf::Color(21, 255, 0));
    grid.addToSceneWithCustomPipeline(scene, bl::rc::UpdateSpeed::Dynamic, PipelineId);

    payload           = &scene->getDescriptorSet<Set>().getBindingPayload<ShaderPayload>();
    payload->gridSize = grid.getSize();
    payload->width    = Width;
    payload->height   = Height;

    resetClock();

    bl::event::Dispatcher::subscribe(this);
}

void MainState::deactivate(bl::engine::Engine& engine) {
    bl::event::Dispatcher::unsubscribe(this);
    engine.renderer().getObserver().popScene();
}

void MainState::update(bl::engine::Engine& engine, float dt, float) {
    if (!paused) {
        residual += dt;
        while (residual >= TickPeriod) {
            residual -= TickPeriod;
            golTick();
            copyData();
        }
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        const sf::Vector2i mpos = sf::Mouse::getPosition(engine.window().getSfWindow());
        const glm::vec2 wpos =
            e->renderer().getObserver().transformToWorldSpace(glm::vec2(mpos.x, mpos.y));
        const glm::vec2 lpos =
            wpos - (grid.getTransform().getGlobalPosition() - grid.getTransform().getOrigin());
        const glm::u32vec2 coord = lpos / CellSize;
        if (coord != prevClick && coord.x < Width && coord.y < Height) {
            prevClick = coord;
            *golFetchPrev(coord.x, coord.y) =
                golFetchPrev(coord.x, coord.y)->species != 0 ? golDead : golSpeciesSources[1];
            copyData();
        }
    }
    else { prevClick.x = std::numeric_limits<unsigned int>::max(); }
}

void MainState::copyData() {
    for (unsigned int x = 0; x < Width; ++x) {
        for (unsigned int y = 0; y < Height; ++y) {
            payload->cells[y * Width + x] = *golFetchPrev(x, y);
        }
    }
}

void MainState::observe(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Space) { paused = !paused; }
        else if (event.key.code == sf::Keyboard::R) { resetClock(); }
        else if (event.key.code == sf::Keyboard::F) { resetFat(); }
        else if (event.key.code == sf::Keyboard::C) { clear(); }
        else if (event.key.code == sf::Keyboard::T) {
            golTick();
            copyData();
        }
    }
    else if (event.type == sf::Event::MouseWheelScrolled) {
        if (event.mouseWheelScroll.delta > 0.f) { e->setTimeScale(e->getTimeScale() * 0.9f); }
        else { e->setTimeScale(e->getTimeScale() * 1.1f); }
    }
}

void MainState::resetFat() {
    golInit(Width, Height);

    sf::Font font;
    font.loadFromFile("Resources/font.ttf");
    sf::Text text(now(), font, 48);
    text.setLetterSpacing(3.7f);
    text.setLineSpacing(0.65f);
    while (text.getGlobalBounds().width + text.getGlobalBounds().left >= Width - 5 &&
           text.getGlobalBounds().height >= Height) {
        text.setCharacterSize(text.getCharacterSize() - 1);
    }
    text.setPosition((Width - text.getGlobalBounds().width) / 2, -text.getGlobalBounds().top);
    sf::RenderTexture rt;
    rt.create(Width, Height);
    rt.clear(sf::Color::Transparent);
    rt.draw(text);
    sf::Image img = rt.getTexture().copyToImage();
    for (unsigned int x = 0; x < Width; ++x) {
        for (unsigned int y = 0; y < Height; ++y) {
            if (img.getPixel(x, y).a > 0) {
                unsigned int i = 0;
                for (unsigned int j = 0; j < text.getString().getSize(); ++j) {
                    const auto cpos = text.findCharacterPos(j);
                    auto glyph = font.getGlyph(text.getString()[j], text.getCharacterSize(), false);
                    glyph.bounds.left = cpos.x;
                    glyph.bounds.top  = cpos.y;
                    if (glyph.bounds.contains(x, y)) {
                        i = j;
                        break;
                    }
                }

                *golFetchPrev(x, Height - y - 1) = golSpeciesSources[i % 3];
            }
        }
    }

    copyData();
}

void MainState::resetClock() {
    golInit(Width, Height);
    golRenderString(now().c_str());
    copyData();
}

void MainState::clear() {
    golInit(Width, Height);
    copyData();
}
