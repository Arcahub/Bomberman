#include "states/RootState.hpp"
#include "ige.hpp"
#include "scripts/TrackballCamera.hpp"
#include "states/MenuState.hpp"
#include "utils/Tag.hpp"

using ige::core::App;
using ige::core::EventChannel;
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
        Transform::from_pos(glm::vec3 { 5.0f, 0.0f, -5.0f }),
        PerspectiveCamera { 70.0f }, CamTag {},
        Scripts::from(TrackballCamera { 12.5f, -0.00460154f, 0.358098f }));

    app.state_machine().push<MenuState>();
}

void RootState::on_update(App& app)
{
    while (const auto& event = m_win_events->next_event()) {
        if (event->kind == WindowEventKind::WindowClose) {
            app.quit();
        }
    }
}
