#include "states/MenuState.hpp"
#include "menu/BackgroundMove.hpp"
#include "menu/MenuLayoutManager.hpp"
#include "utils/GameSettings.hpp"
#include "utils/Tag.hpp"

#include <glm/vec3.hpp>

using ige::asset::Texture;
using ige::core::App;
using ige::core::EventChannel;
using ige::core::State;
using ige::ecs::EntityId;
using ige::ecs::World;
using ige::plugin::audio::AudioClip;
using ige::plugin::audio::AudioListener;
using ige::plugin::audio::AudioSource;
using ige::plugin::render::ImageRenderer;
using ige::plugin::render::RectRenderer;
using ige::plugin::render::Visibility;
using ige::plugin::script::Scripts;
using ige::plugin::transform::Parent;
using ige::plugin::transform::RectTransform;
using ige::plugin::transform::Transform;
using ige::plugin::ui::EventTarget;
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
    auto layout_main_selection_solo_img
        = Texture::make_new("assets/Menu/Bomb/Menus/Main/Menu_main_solo.png");
    auto player_img = Texture::make_new("assets/Menu/Player/menu_player.png");

    const glm::vec2 bombAnchorStart { 0.0f, 0.0f };
    const glm::vec2 bombAnchorEnd { 1.0f, 1.0f };
    const glm::vec2 bombBoundStart { 130.0f, -100.0f };
    const glm::vec2 bombBoundEnd { 100.0f, 150.0f };

    backgroundLayer = app.world().create_entity(RectTransform {});
    foregroundLayer = app.world().create_entity(
        Parent { *backgroundLayer }, RectTransform {});
    bombLayer = app.world().create_entity(
        Parent { *foregroundLayer }, RectTransform {});
    bombUiLayer
        = app.world().create_entity(Parent { *bombLayer }, RectTransform {});

    background = app.world().create_entity(
        Parent { *backgroundLayer },
        RectTransform {}
            .set_anchors({ 0.0f, 0.0f }, { 0.0f, 0.0f })
            .set_bounds({ 0.0f, 0.0f }, { 5758.0f, 5758.0f }),
        ImageRenderer { background_img, ImageRenderer::Mode::TILED },
        Scripts::from(BackgroundMove {}));

    bombSprite = app.world().create_entity(
        Parent { *foregroundLayer },
        RectTransform {}
            .set_anchors(bombAnchorStart, bombAnchorEnd)
            .set_bounds(bombBoundStart, bombBoundEnd),
        ImageRenderer { bomb_img, ImageRenderer::Mode::STRETCHED });

    bombMenuLayout = app.world().create_entity(
        Parent { *bombLayer },
        RectTransform {}
            .set_anchors(bombAnchorStart, bombAnchorEnd)
            .set_bounds(bombBoundStart, bombBoundEnd),
        ImageRenderer { layout_main_menu_bomb_img,
                        ImageRenderer::Mode::STRETCHED },
        Scripts::from(MenuLayoutManager {
            layout_main_menu_bomb_img, layout_main_selection_solo_img, app }));

    playerSprite = app.world().create_entity(
        Parent { *foregroundLayer },
        RectTransform {}
            .set_anchors({ 0.0f, -0.2f }, { 0.2f, 0.9f })
            .set_bounds({ 0.0f, 0.0f }, { 0.0f, 0.0f }),
        ImageRenderer { player_img, ImageRenderer::Mode::STRETCHED });

    bombMenuSelect = app.world().create_entity(
        Parent { *bombUiLayer }, Visibility { 0.8f },
        RectTransform {}
            .set_anchors(bombAnchorStart, bombAnchorEnd)
            .set_bounds(bombBoundStart, bombBoundEnd),
        ImageRenderer { layout_main_selection_solo_img,
                        ImageRenderer::Mode::STRETCHED },
        MenuSelectionTag {} /*EventTarget {}.on<MouseClick>(on_btn_click)*/);

    auto clip = AudioClip::load("./assets/sound/SuperBomberman.ogg");
    audioSource = app.world().create_entity(AudioSource {}, Transform {});
    auto as = app.world().get_component<AudioSource>(audioSource.value());
    as->load_clip(clip);
    as->play();
    audioListener = app.world().create_entity(AudioListener {}, Transform {});
}

void MenuState::on_update(App& app)
{
    auto gs = app.world().get_or_emplace<GameSettings>();
    auto as = app.world().get_component<AudioSource>(audioSource.value());

    as->set_volume(gs.audio * gs.music);

    while (const auto& event = m_win_events->next_event()) {
        if (event->kind == WindowEventKind::WindowClose) {
            app.quit();
        }
    }
}

static void safeDelete(App& app, std::optional<ige::ecs::EntityId> entity)
{
    if (entity.has_value())
        app.world().remove_entity(entity.value());
}

void MenuState::on_stop(App& app)
{
    safeDelete(app, bombSprite);
    safeDelete(app, background);
    safeDelete(app, bombMenuLayout);
    safeDelete(app, bombMenuSelect);
    safeDelete(app, audioSource);
    safeDelete(app, audioListener);
    safeDelete(app, backgroundLayer);
    safeDelete(app, foregroundLayer);
    safeDelete(app, bombLayer);
    safeDelete(app, bombUiLayer);
    safeDelete(app, playerSprite);
}
