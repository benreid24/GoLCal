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

bool Game::completeStartup(bl::engine::Engine& engine) { return true; }

bl::engine::State::Ptr Game::createInitialEngineState() { return MainState::create(); }

void Game::startShutdown() {}

void Game::completeShutdown() {}
