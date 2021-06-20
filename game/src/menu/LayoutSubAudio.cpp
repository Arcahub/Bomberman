#include "menu/LayoutSubAudio.hpp"
#include "menu/MenuLayoutManager.hpp"
#include "utils/GameSettings.hpp"
#include "utils/Tag.hpp"

using ige::ecs::World;
using ige::plugin::render::ImageRenderer;
using ige::plugin::time::Time;
using ige::plugin::transform::Parent;
using ige::plugin::transform::RectTransform;

LayoutSubAudio::LayoutSubAudio(std::optional<ige::ecs::EntityId> lm)
    : layoutManager(lm)
{

    // audio
    layout_settings_selection_audio_audio_icon = Texture::make_new(
        "assets/Menu/Bomb/Menus/Settings/audio/audio_icon.png");
    layout_settings_selection_audio_music_icon = Texture::make_new(
        "assets/Menu/Bomb/Menus/Settings/audio/music_icon.png");
    layout_settings_selection_audio_fx_icon = Texture::make_new(
        "assets/Menu/Bomb/Menus/Settings/audio/fx_icon.png");
    layout_settings_selection_audio_bar
        = Texture::make_new("assets/Menu/Bomb/Menus/Settings/audio/"
                            "Menu_settings_layout_audio_bar.png");
    layout_settings_selection_audio_bar_select
        = Texture::make_new("assets/Menu/Bomb/Menus/Settings/audio/"
                            "Menu_settings_layout_audio_bar_select.png");
    layout_settings_selection_audio_bar_valid
        = Texture::make_new("assets/Menu/Bomb/Menus/Settings/audio/"
                            "Menu_settings_layout_audio_bar_valid.png");
    layout_settings_selection_audio_bar_fill
        = Texture::make_new("assets/Menu/Bomb/Menus/Settings/audio/"
                            "Menu_settings_layout_audio_bar_fill.png");
}

LayoutSubAudio::~LayoutSubAudio()
{
}

void LayoutSubAudio::on_start()
{
    world().create_entity(
        Parent { this->entity() },
        RectTransform {}
            .set_anchors({ 0.50f, 0.65f }, { 0.54f, 0.7f })
            .set_bounds({ 0.0f, 0.0f }, { 0.0f, 0.0f }),
        ImageRenderer { layout_settings_selection_audio_audio_icon,
                        ImageRenderer::Mode::STRETCHED });

    world().create_entity(
        Parent { this->entity() },
        RectTransform {}
            .set_anchors({ 0.50f, 0.45f }, { 0.54f, 0.5f })
            .set_bounds({ 0.0f, 0.0f }, { 0.0f, 0.0f }),
        ImageRenderer { layout_settings_selection_audio_music_icon,
                        ImageRenderer::Mode::STRETCHED });

    world().create_entity(
        Parent { this->entity() },
        RectTransform {}
            .set_anchors({ 0.50f, 0.25f }, { 0.54f, 0.3f })
            .set_bounds({ 0.0f, 0.0f }, { 0.0f, 0.0f }),
        ImageRenderer { layout_settings_selection_audio_fx_icon,
                        ImageRenderer::Mode::STRETCHED });

    audioBar = world().create_entity(
        Parent { this->entity() },
        RectTransform {}
            .set_anchors({ 0.56f, 0.64f }, { 0.85f, 0.71f })
            .set_bounds({ 0.0f, 0.0f }, { 0.0f, 0.0f }),
        ImageRenderer { layout_settings_selection_audio_bar,
                        ImageRenderer::Mode::STRETCHED });

    musicBar = world().create_entity(
        Parent { this->entity() },
        RectTransform {}
            .set_anchors({ 0.56f, 0.44f }, { 0.85f, 0.51f })
            .set_bounds({ 0.0f, 0.0f }, { 0.0f, 0.0f }),
        ImageRenderer { layout_settings_selection_audio_bar,
                        ImageRenderer::Mode::STRETCHED });

    fxBar = world().create_entity(
        Parent { this->entity() },
        RectTransform {}
            .set_anchors({ 0.56f, 0.24f }, { 0.85f, 0.31f })
            .set_bounds({ 0.0f, 0.0f }, { 0.0f, 0.0f }),
        ImageRenderer { layout_settings_selection_audio_bar,
                        ImageRenderer::Mode::STRETCHED });

    const glm::vec2 fillStart = { 0.029f, 0.2f };
    const glm::vec2 fillEnd = { 0.97f, 0.97f };

    audioBarFill = world().create_entity(
        Parent { *audioBar },
        RectTransform {}
            .set_anchors(fillStart, fillEnd)
            .set_bounds({ 0.0f, 0.0f }, { 0.0f, 0.0f }),
        ImageRenderer { layout_settings_selection_audio_bar_fill,
                        ImageRenderer::Mode::STRETCHED });

    musicBarFill = world().create_entity(
        Parent { *musicBar },
        RectTransform {}
            .set_anchors(fillStart, fillEnd)
            .set_bounds({ 0.0f, 0.0f }, { 0.0f, 0.0f }),
        ImageRenderer { layout_settings_selection_audio_bar_fill,
                        ImageRenderer::Mode::STRETCHED });

    fxBarFill = world().create_entity(
        Parent { *fxBar },
        RectTransform {}
            .set_anchors(fillStart, fillEnd)
            .set_bounds({ 0.0f, 0.0f }, { 0.0f, 0.0f }),
        ImageRenderer { layout_settings_selection_audio_bar_fill,
                        ImageRenderer::Mode::STRETCHED });
}

void LayoutSubAudio::updateBarsAction(int id)
{
    auto& gs = world().get_or_emplace<GameSettings>();

    if (id == 10)
        updateBarAction(gs.audio);
    if (id == 11)
        updateBarAction(gs.music);
    if (id == 12)
        updateBarAction(gs.fx);
}

void LayoutSubAudio::updateBarAction(float& data)
{
    ige::plugin::input::InputManager<>* input = get_resource<InputManager<>>();

    if (input->keyboard().is_down(KeyboardKey::KEY_ARROW_RIGHT) && data < 1)
        data += 0.01f;

    if (input->keyboard().is_down(KeyboardKey::KEY_ARROW_LEFT) && data > 0)
        data -= 0.01f;
}

void LayoutSubAudio::setBarTexture(
    int id, std::optional<ige::ecs::EntityId> ent)
{
    ige::plugin::input::InputManager<>* input = get_resource<InputManager<>>();
    auto scripts = world().get_component<Scripts>(layoutManager.value());
    auto lm = scripts->get<MenuLayoutManager>();
    auto ir = world().get_component<ImageRenderer>(ent.value());

    if (lm->selectionID == id) {
        if (lm->lockMove) {
            ir->texture = layout_settings_selection_audio_bar_valid;
            updateBarsAction(lm->selectionID);
            if (input->keyboard().is_pressed(KeyboardKey::KEY_SPACE)) {
                lm->lockMove = false;
                lm->dirty = true;
            }
        } else {
            ir->texture = layout_settings_selection_audio_bar_select;
        }
    } else {
        ir->texture = layout_settings_selection_audio_bar;
    }
}

void LayoutSubAudio::update()
{
    return;
    auto gs = world().get_or_emplace<GameSettings>();
    RectTransform* audioBar = nullptr;
    RectTransform* musicBar = nullptr;
    RectTransform* fxBar = nullptr;

    if (audioBarFill) {
        audioBar = world().get_component<RectTransform>(audioBarFill.value());
        if (audioBar) {
            audioBar->anchors_max = glm::vec2 { gs.audio * 0.97f, 0.8f };
            setBarTexture(10, audioBarFill);
        }
    }

    if (musicBarFill) {
        musicBar = world().get_component<RectTransform>(musicBarFill.value());
        if (musicBar) {
            musicBar->anchors_max = glm::vec2 { gs.music * 0.97f, 0.8f };
            setBarTexture(11, musicBarFill);
        }
    }

    if (fxBarFill) {
        fxBar = world().get_component<RectTransform>(fxBarFill.value());
        if (fxBar) {
            fxBar->anchors_max = glm::vec2 { gs.fx * 0.97f, 0.8f };
            setBarTexture(12, fxBarFill);
        }
    }
}
