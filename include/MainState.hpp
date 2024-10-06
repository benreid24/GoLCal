#ifndef CORE_DEMOENGINESTATE_HPP
#define CORE_DEMOENGINESTATE_HPP

#include <BLIB/Cameras/2D/Camera2D.hpp>
#include <BLIB/Engine/Engine.hpp>
#include <BLIB/Graphics.hpp>

/**
 * @brief Basic engine state that provides a spinning triangle
 */
class MainState : public bl::engine::State {
public:
    static constexpr float DegPerSec = 90.f;

    static bl::engine::State::Ptr create() { return Ptr(new MainState()); }

    virtual const char* name() const override;

    virtual void activate(bl::engine::Engine& engine) override;

    virtual void deactivate(bl::engine::Engine& engine) override;

    virtual void update(bl::engine::Engine&, float dt, float) override;

private:
    bl::gfx::Triangle triangle;

    MainState()
    : State(bl::engine::StateMask::Running) {}
};

#endif
