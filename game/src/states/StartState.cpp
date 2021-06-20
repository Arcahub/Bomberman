#include "states/StartState.hpp"
#include "menu/BackgroundMove.hpp"
#include "menu/MenuLayoutManager.hpp"
#include "states/MenuState.hpp"
#include "states/ResultState.hpp"
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

void StartState::on_start(App& app)
{
    auto channel = app.world().get<EventChannel<WindowEvent>>();
    m_win_events.emplace(channel->subscribe());

    auto background_img
        = Texture::make_new("assets/Menu/Background/background_blue.png");
    auto logo_img = Texture::make_new("assets/Bomberman_logo.png");
    auto press_img = Texture::make_new("assets/Text/press_action.png");

    backgroundLayer = app.world().create_entity(RectTransform {});
    foregroundLayer = app.world().create_entity(
        Parent { *backgroundLayer }, RectTransform {});

    background = app.world().create_entity(
        Parent { *backgroundLayer },
        RectTransform {}
            .set_anchors({ 0.0f, 0.0f }, { 0.0f, 0.0f })
            .set_bounds({ 0.0f, 0.0f }, { 5758.0f, 5758.0f }),
        ImageRenderer { background_img, ImageRenderer::Mode::TILED },
        Scripts::from(BackgroundMove {}));

    logo = app.world().create_entity(
        Parent { *foregroundLayer },
        RectTransform {}
            .set_anchors({ 0.2f, 0.5f }, { 0.8f, 0.9f })
            .set_bounds({ 0.0f, 0.0f }, { 0.0f, 0.0f }),
        ImageRenderer { logo_img, ImageRenderer::Mode::STRETCHED });

    press = app.world().create_entity(
        Parent { *foregroundLayer },
        RectTransform {}
            .set_anchors({ 0.4f, 0.2f }, { 0.6f, 0.3f })
            .set_bounds({ 0.0f, 0.0f }, { 0.0f, 0.0f }),
        ImageRenderer { press_img, ImageRenderer::Mode::STRETCHED });

    auto gs = app.world().get_or_emplace<GameSettings>();
    auto clip = AudioClip::load("./assets/sound/Destroy_Them.ogg");
    audioSource = app.world().create_entity(AudioSource {}, Transform {});
    auto as = app.world().get_component<AudioSource>(audioSource.value());
    as->set_volume(gs.audio * gs.music);
    as->load_clip(clip);
    as->set_looping(false);
    as->play();
    audioListener = app.world().create_entity(AudioListener {}, Transform {});
}

void StartState::on_update(App& app)
{
    /*auto gs = app.world().get_or_emplace<GameSettings>();
    auto as = app.world().get_component<AudioSource>(audioSource.value());

    as->set_volume(gs.audio * gs.music);*/

    ige::plugin::input::InputManager<>* input
        = app.world().get<InputManager<>>();

    if (input->keyboard().is_released(KeyboardKey::KEY_SPACE)) {
        app.state_machine().switch_to<MenuState>();
    }

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

void StartState::on_stop(App& app)
{
    safeDelete(app, logo);
    safeDelete(app, background);
    safeDelete(app, backgroundLayer);
    safeDelete(app, foregroundLayer);
    safeDelete(app, press);
    safeDelete(app, audioListener);
    safeDelete(app, audioSource);
}
