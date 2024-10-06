#include <MainState.hpp>

#include <Constants.hpp>
#include <DescriptorSet.hpp>
#include <gol/gol.h>

namespace
{} // namespace

const char* MainState::name() const { return "MainState"; }

void MainState::activate(bl::engine::Engine& engine) {
    auto scene = engine.renderer().getObserver().pushScene<bl::rc::scene::Scene2D>();
    engine.renderer().getObserver().setCamera<bl::cam::Camera2D>(WindowSize * 0.5f, WindowSize);
    engine.renderer().getObserver().setClearColor(bl::sfcol(sf::Color::Cyan));

    // TODO - get descriptor set from pipeline and set data

    grid.create(engine, glm::vec2(Width * CellSize, Height * CellSize));
    grid.getTransform().setOrigin(grid.getSize() * 0.5f);
    grid.getTransform().setPosition(WindowSize * 0.5f);
    grid.setFillColor(sf::Color::Red);
    grid.addToSceneWithCustomPipeline(scene, bl::rc::UpdateSpeed::Dynamic, PipelineId);
}

void MainState::deactivate(bl::engine::Engine& engine) {
    engine.renderer().getObserver().popScene();
}

void MainState::update(bl::engine::Engine&, float dt, float) {
    residual += dt;
    while (residual >= TickPeriod) {
        residual -= TickPeriod;
        golTick();
        // TODO - fetch state and update descriptor
    }
}