#ifndef GAME_HPP
#define GAME_HPP

#include <BLIB/Game.hpp>

class Game : public bl::game::Game {
public:
protected:
    /**
     * @brief Called at the beginning of main(). Loads game config and properties
     *
     * @param argc The number of arguments passed to main()
     * @param argv The arguments passed to main()
     * @return True on success, false to exit
     */
    virtual bool performEarlyStartup(int argc, char** argv) override;

    /**
     * @brief Creates the parameters to launch the engine with
     */
    virtual bl::engine::Settings createStartupParameters() override;

    /**
     * @brief Creates game-specific systems, sets up the input mappings, etc
     *
     * @param engine The game engine instance
     * @return True on success, false to exit
     */
    virtual bool completeStartup(bl::engine::Engine& engine) override;

    /**
     * @brief Creates the engine state to launch the game with
     */
    virtual bl::engine::State::Ptr createInitialEngineState() override;

    /**
     * @brief Called after the main engine loop while the engine instance exists
     */
    virtual void startShutdown() override;

    /**
     * @brief Called at the end of main() after the engine instance is destroyed
     */
    virtual void completeShutdown() override;
};

#endif
