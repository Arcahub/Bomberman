#include "RootState.hpp"
#include "ige.hpp"
#include <chrono>
#include <iostream>
#include <optional>

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
; // TODO: https://bit.ly/3hhMJ58

using glm::vec3;
using glm::vec4;
using ige::core::App;
using ige::core::EventChannel;
using ige::core::State;
using ige::ecs::Schedule;
using ige::ecs::World;
using ige::plugin::gltf::GltfFormat;
using ige::plugin::gltf::GltfScene;
using ige::plugin::input::InputManager;
using ige::plugin::input::KeyboardKey;
using ige::plugin::render::PerspectiveCamera;
using ige::plugin::transform::Transform;
using ige::plugin::window::WindowEvent;
using ige::plugin::window::WindowEventKind;

void RootState::on_start(App& app)
{
    auto channel = app.world().get<EventChannel<WindowEvent>>();
    m_win_events.emplace(channel->subscribe());

    app.world().create_entity(
        Transform::from_pos(vec3(20.0f, 10.0f, 0.0f)).look_at(vec3(0.0f)),
        PerspectiveCamera(90.0f));

    m_cube = app.world()
                 .create_entity(
                     Transform {},
                     GltfScene {
                         "assets/OrientationTest.glb",
                         GltfFormat::BINARY,
                     })
                 .id();
}

void RootState::on_update(App& app)
{
    // quit app when window is closed
    while (auto event = m_win_events->next_event()) {
        if (event->kind == WindowEventKind::WindowClose) {
            app.quit();
        }
    }

    Transform* xform = app.world().get_component<Transform>(*m_cube);

    InputManager* manager = app.world().get<InputManager>();

    bool translate = manager->keyboard().is_down(KeyboardKey::KEY_SHIFT_LEFT);

    if (manager->keyboard().is_down(KeyboardKey::KEY_ARROW_RIGHT)) {
        if (translate) {
            xform->translate(vec3 { 0.0f, 0.0f, -0.2f });
        } else {
            xform->rotate(vec3 { 0.0f, 1.0f, 0.0f });
        }
    }

    if (manager->keyboard().is_down(KeyboardKey::KEY_ARROW_LEFT)) {
        if (translate) {
            xform->translate(vec3 { 0.0f, 0.0f, 0.2f });
        } else {
            xform->rotate(vec3 { 0.0f, -1.0f, 0.0f });
        }
    }

    if (manager->keyboard().is_down(KeyboardKey::KEY_ARROW_UP)) {
        xform->scale(vec3(1.01f));
    }

    if (manager->keyboard().is_down(KeyboardKey::KEY_ARROW_DOWN)) {
        xform->scale(vec3(0.99f));
    }
}
