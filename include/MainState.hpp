#ifndef CORE_DEMOENGINESTATE_HPP
#define CORE_DEMOENGINESTATE_HPP

#include <BLIB/Cameras/2D/Camera2D.hpp>
#include <BLIB/Engine/Engine.hpp>
#include <BLIB/Events.hpp>
#include <BLIB/Graphics.hpp>
#include <DescriptorSet.hpp>

/**
 * @brief Basic engine state that provides a spinning triangle
 */
class MainState
: public bl::engine::State
, public bl::event::Listener<sf::Event> {
public:
    static bl::engine::State::Ptr create() { return Ptr(new MainState()); }

    virtual const char* name() const override;

    virtual void activate(bl::engine::Engine& engine) override;

    virtual void deactivate(bl::engine::Engine& engine) override;

    virtual void update(bl::engine::Engine&, float dt, float) override;

private:
    bl::engine::Engine* e;
    bl::gfx::Rectangle grid;
    float residual;
    ShaderPayload* payload;
    bool paused;
    glm::u32vec2 prevClick;

    MainState();
    void clear();
    void resetFat();
    void resetClock();
    void copyData();
    virtual void observe(const sf::Event& event) override;
};

#endif
