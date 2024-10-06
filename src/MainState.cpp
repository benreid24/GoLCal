#include <MainState.hpp>

const char* MainState::name() const { return "MainState"; }

void MainState::activate(bl::engine::Engine& engine) {
    auto scene = engine.renderer().getObserver().pushScene<bl::rc::scene::Scene2D>();
    engine.renderer().getObserver().setCamera<bl::cam::Camera2D>(glm::vec2(860.f, 540.f),
                                                                 glm::vec2(1920.f, 1080.f));
    engine.renderer().getObserver().setClearColor(bl::sfcol(sf::Color::Cyan));

    triangle.create(engine, {0.f, 173.f}, {200.f, 173.f}, {100.f, 0.f});
    triangle.setColorGradient({1.f, 0.f, 0.f, 1.f}, {0.f, 1.f, 0.f, 1.f}, {0.f, 0.f, 1.f, 1.f});
    triangle.getTransform().setPosition(400.f, 300.f);
    triangle.getTransform().setOrigin({100.f, 123.f});
    triangle.addToScene(scene, bl::rc::UpdateSpeed::Dynamic);

    BL_LOG_INFO << "MainState activated";
}

void MainState::deactivate(bl::engine::Engine& engine) {
    engine.renderer().getObserver().popScene();
}

void MainState::update(bl::engine::Engine&, float dt, float) {
    triangle.getTransform().rotate(dt * DegPerSec);
}