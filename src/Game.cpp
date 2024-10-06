#include <Game.hpp>

#include <MainState.hpp>
#include <iostream>

namespace
{
// one instance should exist globally
Game game;
} // namespace

bool Game::performEarlyStartup(int argc, char** argv) {
    // TODO - SETUP_TASK - any other game specific early setup steps

    return true;
}

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
    // TODO - SETUP_TASK - register game specific systems

    return true;
}

bl::engine::State::Ptr Game::createInitialEngineState() {
    // TODO - SETUP_TASK - create actual initial state
    return MainState::create();
}

void Game::startShutdown() {
    // TODO - SETUP_TASK - any early shutdown tasks
}

void Game::completeShutdown() {
    // TODO - SETUP_TASK - any final shutdown tasks
}
