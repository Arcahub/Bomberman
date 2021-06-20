#include "states/ResultState.hpp"
#include "menu/BackgroundMove.hpp"
#include "menu/MenuLayoutManager.hpp"
#include "states/MenuState.hpp"
#include "utils/GameSettings.hpp"
#include "utils/Score.hpp"
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

void ResultState::on_start(App& app)
{
    auto channel = app.world().get<EventChannel<WindowEvent>>();
    m_win_events.emplace(channel->subscribe());

    auto background_img
        = Texture::make_new("assets/Menu/Background/background_blue.png");
    std::initializer_list<ige::asset::Texture::Handle> players_img
        = { Texture::make_new("assets/Menu/Player/player_blue.png"),
            Texture::make_new("assets/Menu/Player/player_red.png"),
            Texture::make_new("assets/Menu/Player/player_yellow.png"),
            Texture::make_new("assets/Menu/Player/player_lime.png") };
    std::initializer_list<ige::asset::Texture::Handle> podium_img
        = { Texture::make_new("assets/Menu/result/podium_1.png"),
            Texture::make_new("assets/Menu/result/podium_2.png"),
            Texture::make_new("assets/Menu/result/podium_3.png"),
            Texture::make_new("assets/Menu/result/podium_4.png") };

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

    auto gs = app.world().get_or_emplace<GameSettings>();
    std::shared_ptr<AudioClip> clip(
        new AudioClip("./assets/sound/resultMusic.ogg"));
    audioSource = app.world().create_entity(AudioSource {}, Transform {});
    auto as = app.world().get_component<AudioSource>(audioSource.value());
    as->set_volume(gs.audio * gs.music);
    as->load_clip(clip);
    as->set_looping(false);
    as->play();
    audioListener = app.world().create_entity(AudioListener {}, Transform {});

    // set podium
    auto score = app.world().get<Score>();

    if (!score)
        return;

    for (std::size_t i = 0; i < 4 || i < score->scoreboard.size(); i++) {
        std::cout << score->scoreboard[i] << std::endl;
        ige::asset::Texture::Handle podium = *(podium_img.begin() + i);
        app.world().create_entity(
            Parent { *foregroundLayer },
            RectTransform {}
                .set_anchors(
                    { 0.25f * (score->scoreboard[i] - 1), 0.0f },
                    { 0.25f * score->scoreboard[i], 1.0f })
                .set_bounds({ 0.0f, 0.0f }, { 0.0f, 0.0f }),
            ImageRenderer { podium, ImageRenderer::Mode::STRETCHED });
    }
}

void ResultState::on_update(App& app)
{
    /*auto gs = app.world().get_or_emplace<GameSettings>();
    auto as = app.world().get_component<AudioSource>(audioSource.value());

    as->set_volume(gs.audio * gs.music);*/

    ige::plugin::input::InputManager<>* input
        = app.world().get<InputManager<>>();

    if (input->is_action_down("action") && *input->is_action_down("action")) {
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

void ResultState::on_stop(App& app)
{
    safeDelete(app, background);
    safeDelete(app, backgroundLayer);
    safeDelete(app, foregroundLayer);
    safeDelete(app, audioListener);
    safeDelete(app, audioSource);
}
