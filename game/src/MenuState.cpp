#include "MenuState.hpp"
#include "scripts.hpp"

#include <glm/vec3.hpp>

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
using ige::plugin::gltf::GltfScene;
using ige::plugin::render::ImageRenderer;
using ige::plugin::render::PerspectiveCamera;
using ige::plugin::render::RectRenderer;
using ige::plugin::render::Visibility;
using ige::plugin::script::CppBehaviour;
using ige::plugin::script::Scripts;
using ige::plugin::transform::Parent;
using ige::plugin::transform::RectTransform;
using ige::plugin::transform::Transform;
using ige::plugin::ui::EventTarget;
using ige::plugin::ui::event::MouseClick;
using ige::plugin::ui::event::MouseEnter;
using ige::plugin::ui::event::MouseLeave;
using ige::plugin::window::WindowEvent;
using ige::plugin::window::WindowEventKind;

void MenuState::on_start(App& app)
{
    auto channel = app.world().get<EventChannel<WindowEvent>>();
    m_win_events.emplace(channel->subscribe());

    auto btn_img
        = Texture::make_new("assets/Menu/Background/background_blue.png");

    auto bottom_pane = app.world().create_entity(
        Visibility { 0.8f },
        RectTransform {}
            .set_anchors({ 0.0f, 0.0f }, { 1.0f, 0.0f })
            .set_bounds({ 0.0f, 0.0f }, { 0.0f, 50.0f }),
        RectRenderer {}.set_fill_rgb(0xFFFFFF));

    auto on_btn_click = [=](World& w, const EntityId&, const MouseClick&) {
        std::cout << "Button was clicked!" << std::endl;

        auto vis = w.get_component<Visibility>(bottom_pane);

        if (vis) {
            vis->visible = !vis->visible;
        }
    };

    app.world().create_entity(
        Parent { bottom_pane },
        RectTransform {}
            .set_anchors({ 0.0f, 0.5f })
            .set_bounds({ 5.0f, -20.0f }, { 200.0f, 20.0f }),
        ImageRenderer { btn_img, ImageRenderer::Mode::SLICED }.set_tint_rgb(
            0xfce37e),
        EventTarget {}.on<MouseClick>(on_btn_click));

    app.world().create_entity(
        RectTransform {}
            .set_anchors({ 0.0f, 1.0f }, { 1.0f, 1.0f })
            .set_bounds({ 100.0f, -100.0f }, { -100.0f, -10.0f }),
        ImageRenderer { btn_img, ImageRenderer::Mode::TILED });

    app.world().create_entity(PerspectiveCamera { 70.0f });
}

void MenuState::on_update(App& app)
{
    while (const auto& event = m_win_events->next_event()) {
        if (event->kind == WindowEventKind::WindowClose) {
            app.quit();
        }
    }
}