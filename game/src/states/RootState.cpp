#include "states/RootState.hpp"
#include "ige.hpp"
#include "scripts/TrackballCamera.hpp"
#include "states/MenuState.hpp"
#include "utils/GameSettings.hpp"
#include "utils/Tag.hpp"
#include <iostream>

using ige::core::App;
using ige::core::EventChannel;
using ige::plugin::input::Bindings;
using ige::plugin::input::InputManager;
using ige::plugin::input::KeyboardKey;
using ige::plugin::render::PerspectiveCamera;
using ige::plugin::script::Scripts;
using ige::plugin::transform::Transform;
using ige::plugin::window::WindowEvent;
using ige::plugin::window::WindowEventKind;

void RootState::on_start(App& app)
{
    auto channel = app.world().get<EventChannel<WindowEvent>>();
    m_win_events.emplace(channel->subscribe());

    app.world().create_entity(
        PerspectiveCamera { 70.0f }, CamTag {},
        Scripts::from(TrackballCamera { 15.0f, -0.00460154f, 0.368098f }));

    app.state_machine().push<MenuState>();

    if (auto input = app.world().get<InputManager<>>()) {
        input->bindings
            = Bindings<>::from_file("./assets/config/bindings.json");
        if (!input->bindings.has_value()) {
            std::cout << "Could not load bindings settings." << std::endl;
        }
    }

    GameSettings gd;
    app.world().insert(&gd);
}

void RootState::on_update(App& app)
{
    while (const auto& event = m_win_events->next_event()) {
        if (event->kind == WindowEventKind::WindowClose) {
            app.quit();
        }
    }
}

void RootState::on_stop(App& app)
{
    /*if (auto manager = app.world().get<InputManager<>>()) {
        manager->bindings->to_file("./assets/config/bindings.json");
    }*/
}
