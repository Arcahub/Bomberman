#include "RootState.hpp"
#include "MapGenerator.hpp"
#include "TrackballCamera.hpp"
#include "ige.hpp"
#include "scripts.hpp"
#include <chrono>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <iostream>
#include <optional>

using glm::vec2;
using glm::vec3;
using glm::vec4;

using ige::asset::Material;
using ige::asset::Mesh;
using ige::asset::Texture;

using ige::core::App;
using ige::core::EventChannel;
using ige::core::State;
using ige::ecs::EntityId;
using ige::ecs::Schedule;
using ige::ecs::World;
using ige::plugin::audio::AudioClip;
using ige::plugin::audio::AudioListener;
using ige::plugin::audio::AudioSource;
using ige::plugin::gltf::GltfFormat;
using ige::plugin::gltf::GltfPlugin;
using ige::plugin::gltf::GltfScene;
using ige::plugin::input::InputManager;
using ige::plugin::input::InputPlugin;
using ige::plugin::input::KeyboardKey;
using ige::plugin::render::MeshRenderer;
using ige::plugin::render::PerspectiveCamera;
using ige::plugin::script::CppBehaviour;
using ige::plugin::script::Scripts;
using ige::plugin::transform::Transform;
using ige::plugin::window::WindowEvent;
using ige::plugin::window::WindowEventKind;

void RootState::on_start(App& app)
{
    auto channel = app.world().get<EventChannel<WindowEvent>>();
    m_win_events.emplace(channel->subscribe());

    auto cube_mesh = Mesh::make_cube(1.0f);
    auto ground_mat = Material::make_default();
    ground_mat->set("base_color_factor", vec4 { 1.0f, 0.5f, 0.85f, 1.0f });

    std::shared_ptr<AudioClip> clip(
        new AudioClip("./assets/sound/SuperBomberman.ogg"));
    auto source = app.world().create_entity(AudioSource {}, Transform {});
    auto audiosource = app.world().get_component<AudioSource>(source);
    audiosource->load_clip(clip);
    audiosource->play();
    auto listener = app.world().create_entity(AudioListener {}, Transform {});

    auto mapEntity = app.world().create_entity(Scripts::from(MapGenerator {}));

    app.world().create_entity(
        PerspectiveCamera { 70.0f }, Scripts::from(TrackballCamera { 10.0f }));
}

void RootState::on_update(App& app)
{
    while (const auto& event = m_win_events->next_event()) {
        if (event->kind == WindowEventKind::WindowClose) {
            app.quit();
        }
    }
}
