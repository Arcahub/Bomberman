#include "MenuState.hpp"
#include "RootState.hpp"
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

    auto background_img
        = Texture::make_new("assets/Menu/Background/background_blue.png");
    auto bomb_img = Texture::make_new("assets/Menu/Bomb/Bomb.png");
    auto notif_img = Texture::make_new("assets/Menu/Bomb/Notif_bar.png");
    auto layout_main_menu_bomb_img
        = Texture::make_new("assets/Menu/Bomb/Menus/Main/Menu_main_layout.png");
    auto layout_play_img
        = Texture::make_new("assets/Menu/Bomb/Menus/Main/Menu_main_solo.png");

    // app.state_machine().switch_to<RootState>();

    /*app.world().create_entity(
        RectTransform {}
            .set_anchors({ 0.0f, 0.0f }, { 0.0f, 0.0f })
            .set_bounds({ 0.0f, 0.0f }, { 1920.0f, 1080.0f }),
        ImageRenderer { background_img, ImageRenderer::Mode::STRETCHED });*/

    app.world().create_entity(
        RectTransform {}
            .set_anchors({ 0.55f, 0.5f }, { 0.55f, 0.5f })
            .set_bounds({ -900.0f, -658.5f }, { 900.0f, 658.5f }),
        ImageRenderer { bomb_img, ImageRenderer::Mode::STRETCHED });

    app.world().create_entity(
        RectTransform {}
            .set_anchors({ 0.5f, 0.95f }, { 0.5f, 0.95f })
            .set_bounds({ -656.75f, -42.0f }, { 656.75f, 42.0f }),
        ImageRenderer { notif_img, ImageRenderer::Mode::STRETCHED });

    app.world().create_entity(
        RectTransform {}
            .set_anchors({ 0.55f, 0.5f }, { 0.55f, 0.5f })
            .set_bounds({ -900.0f, -658.5f }, { 900.0f, 658.5f }),
        ImageRenderer { layout_main_menu_bomb_img,
                        ImageRenderer::Mode::STRETCHED });

    /*auto bottom_pane = app.world().create_entity(
        Visibility { 0.8f },
        RectTransform {}
            .set_anchors({ 0.54f, 0.5f }, { 0.54f, 0.5f })
            .set_bounds({ -200.0f, -200.0f }, { 200.0f, 200.0f }),
        RectRenderer {}.set_fill_rgb(0xFFFFFF));*/

    /*auto on_btn_click = [=](World& w, const EntityId&, const MouseClick&) {
        std::cout << "Button was clicked!" << std::endl;

        auto vis = w.get_component<Visibility>(play_ent);

        if (vis) {
            vis->visible = !vis->visible;
        }
    };

    play_ent = app.world().create_entity(
        Visibility { 0.8f },
        RectTransform {}
            .set_anchors({ 0.55f, 0.5f }, { 0.55f, 0.5f })
            .set_bounds({ -900.0f, -658.5f }, { 900.0f, 658.5f }),
        ImageRenderer { layout_play_img, ImageRenderer::Mode::STRETCHED },
        EventTarget {}.on<MouseClick>(on_btn_click));*/

    /*app.world().create_entity(
        RectTransform {}
            .set_anchors({ 0.0f, 1.0f }, { 1.0f, 1.0f })
            .set_bounds({ 100.0f, -100.0f }, { -100.0f, -10.0f }),
        ImageRenderer { layout_play_img, ImageRenderer::Mode::TILED });*/

    app.world().create_entity(
        Transform {}
            .set_translation(glm::vec3 { 0.0f, -1.0f, 0.0f })
            .set_scale(glm::vec3 { 1.0f, 0.5f, 1.0f }),
        GltfScene {
            "assets/Models/BACKGROUND.glb",
            GltfFormat::BINARY,
        });

    app.world().create_entity(
        Transform::from_pos(glm::vec3(0.0f, 0.0f, 0.0f)).set_scale(0.25f),
        GltfScene {
            "assets/Bomberman_Play.glb",
            GltfFormat::BINARY,
        });

    std::shared_ptr<AudioClip> clip(
        new AudioClip("./assets/sound/SuperBomberman.ogg"));
    auto source = app.world().create_entity(AudioSource {}, Transform {});
    auto audiosource = app.world().get_component<AudioSource>(source);
    audiosource->load_clip(clip);
    audiosource->play();
    auto listener = app.world().create_entity(AudioListener {}, Transform {});

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