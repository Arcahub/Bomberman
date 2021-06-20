#include "menu/MenuLayoutManager.hpp"
#include "menu/LayoutSubAudio.hpp"
#include "menu/LayoutSubControls.hpp"
#include "menu/LayoutSubDisplay.hpp"
#include "states/PreSoloGameState.hpp"
#include "states/RoomLocalState.hpp"
#include "states/RoomState.hpp"
#include "utils/GameSettings.hpp"
#include "utils/Tag.hpp"
#include <chrono>
#include <functional>

using ige::ecs::World;
using ige::plugin::input::InputManager;
using ige::plugin::render::ImageRenderer;
using ige::plugin::time::Time;
using ige::plugin::transform::Parent;
using ige::plugin::transform::RectTransform;
using ige::plugin::transform::Transform;

// LINK TO GAME :

void MenuLayoutManager::goToSolo()
{
    // app.state_machine().switch_to<PreSoloGameState>();
}

void MenuLayoutManager::goToLocal()
{
    app.state_machine().switch_to<RoomLocalState>();
}

void MenuLayoutManager::goToMultiHost()
{
    // app.state_machine().switch_to<RoomState>();
}

void MenuLayoutManager::goToMultiJoin()
{
    app.state_machine().switch_to<RoomState>(true);
}

// =============

// Menu layout map data

static const int main_menu_map[3][7] = { {
                                             4,
                                             0,
                                             1,
                                             -2,
                                         },
                                         { -1, 2, 3, -2 },
                                         { -3, -3, -3, -3 } };

static const int settings_menu_audio_map[4][7] = {
    { 3, 0, 10, -2 }, { 3, 1, 11, -2 }, { 3, 2, 12, -2 }, { -3, -3, -3, -3 }
};

static const int settings_menu_display_map[4][7] = {
    { 3, 1, -2, -2 }, { 3, 0, -2, -2 }, { 3, 2, -2, -2 }, { -3, -3, -3, -3 }
};

static const int settings_menu_controls_map[6][7]
    = { { 3, 2, 10, 20, 30, 40, -2 },   { 3, 1, 11, 21, 31, 41, -2 },
        { 3, 0, 12, 22, 32, 42, -2 },   { -1, -1, 13, 23, 33, 43, -2 },
        { -1, -1, 14, 24, 34, 44, -2 }, { -3, -3, -3, -3, -3, -3, -3 } };

static const int multi_menu_map[2][7] = { {
                                              2,
                                              0,
                                              1,
                                              -2,
                                          },
                                          { -3, -3, -3, -3 } };

static const int multi_menu_online_map[2][7] = { {
                                                     2,
                                                     0,
                                                     1,
                                                     -2,
                                                 },
                                                 { -3, -3, -3, -3 } };

static const int help_menu_map[2][7] = { {
                                             0,
                                             -2,
                                             -2,
                                             -2,
                                         },
                                         { -3, -3, -3, -3 } };

static const int (*layout[])[7] = {
    main_menu_map,
    settings_menu_audio_map,
    settings_menu_display_map,
    settings_menu_controls_map,
    help_menu_map,
    multi_menu_map,
    multi_menu_online_map,
};

// Menu Layout Manager

MenuLayoutManager::MenuLayoutManager(
    Texture::Handle layout_start, Texture::Handle layout_select,
    ige::core::App& app)
    : app(app)
{
    action_clock = std::chrono::steady_clock::now();
    layout_main_img = layout_start;
    layout_main_selection_solo_img = layout_select;
}

MenuLayoutManager::~MenuLayoutManager()
{
}

void MenuLayoutManager::on_start()
{
    // === load all textures ===

    // == layout ==

    layout_settings_audio_img = Texture::make_new(
        "assets/Menu/Bomb/Menus/Settings/audio/Menu_settings_layout_audio.png");
    layout_settings_display_img
        = Texture::make_new("assets/Menu/Bomb/Menus/Settings/display/"
                            "Menu_settings_layout_display.png");
    layout_settings_controls_img
        = Texture::make_new("assets/Menu/Bomb/Menus/Settings/controls/"
                            "Menu_settings_layout_controls.png");
    layout_multi_img = Texture::make_new(
        "assets/Menu/Bomb/Menus/Multi/Menu_Multi_layout.png");
    layout_multi_online_img
        = Texture::make_new("assets/Menu/Bomb/Menus/Multi/online/"
                            "Menu_Multi_layout_online_layout.png");
    layout_help_img = Texture::make_new("assets/Menu/Bomb/Menus/help/"
                                        "Menu_help_layout.png");

    // == selection ==

    // main
    layout_main_selection_multi_img
        = Texture::make_new("assets/Menu/Bomb/Menus/Main/Menu_main_multi.png");
    layout_main_selection_settings_img = Texture::make_new(
        "assets/Menu/Bomb/Menus/Main/Menu_main_settings.png");
    layout_main_selection_exit_img
        = Texture::make_new("assets/Menu/Bomb/Menus/Main/Menu_main_exit.png");
    layout_main_selection_tuto_img
        = Texture::make_new("assets/Menu/Bomb/Menus/Main/Menu_main_tuto.png");

    // settings
    layout_settings_selection_back_img = Texture::make_new(
        "assets/Menu/Bomb/Menus/Settings/Menu_settings_back.png");
    layout_settings_selection_side_audio_img = Texture::make_new(
        "assets/Menu/Bomb/Menus/Settings/Menu_settings_side_audio.png");
    layout_settings_selection_side_display_img = Texture::make_new(
        "assets/Menu/Bomb/Menus/Settings/Menu_settings_side_display.png");
    layout_settings_selection_side_controls_img = Texture::make_new(
        "assets/Menu/Bomb/Menus/Settings/Menu_settings_side_controls.png");

    // multi menu sprites
    layout_multi_selection_online_img = Texture::make_new(
        "assets/Menu/Bomb/Menus/Multi/Menu_Multi_layout_online.png");
    layout_multi_selection_local_img = Texture::make_new(
        "assets/Menu/Bomb/Menus/Multi/Menu_Multi_layout_local.png");
    // multi online menu sprites
    layout_multi_selection_online_host_img
        = Texture::make_new("assets/Menu/Bomb/Menus/Multi/online/"
                            "Menu_Multi_layout_online_host.png");
    layout_multi_selection_online_join_img
        = Texture::make_new("assets/Menu/Bomb/Menus/Multi/online/"
                            "Menu_Multi_layout_online_join.png");
    // multi online menu sprites
    layout_settings_help_img
        = Texture::make_new("assets/Menu/Bomb/Menus/help/Menu_help_layout.png");

    // ausio
    audio_wrong = AudioClip::load("./assets/sound/Menu_error.ogg");
    audio_valid = AudioClip::load("./assets/sound/Menu_valid.ogg");
    audio_move = AudioClip::load("./assets/sound/Menu_move.ogg");

    audioSource = app.world().create_entity(AudioSource {}, Transform {});
}

void MenuLayoutManager::playSound(
    std::shared_ptr<ige::plugin::audio::AudioClip> ac)
{
    auto gs = app.world().get_or_emplace<GameSettings>();
    auto as = world().get_component<AudioSource>(audioSource.value());
    if (!as || !ac)
        return;
    as->stop();
    as->set_looping(false);
    as->load_clip(ac);
    as->set_volume(gs.audio * gs.fx);
    as->play();
}

glm::vec2 MenuLayoutManager::currentPos()
{
    auto& currentLayout = layout[layoutID];

    for (int y = 0; currentLayout[y][0] != -3; y++) {
        for (int x = 0; currentLayout[y][x] != -2; x++) {
            if (currentLayout[y][x] == selectionID)
                return glm::vec2 { x, y };
        }
    }

    selectionID = 0;
    return currentPos();
}

glm::vec2 MenuLayoutManager::currentMapSize()
{
    const auto& currentLayout = layout[layoutID];
    glm::vec2 size { 0, 0 };

    for (; currentLayout[(int)size.y][0] != -3; size.y++) {
        for (int x = 0; currentLayout[(int)size.y][x] != -2; x++) {
            if (size.x < x)
                size.x = x;
        }
    }

    return size;
}

void MenuLayoutManager::switchSettings(int id)
{
    if (layoutID == id)
        return;
    layoutID = id;
    if (SettingsSubLayout.has_value()) {
        world().remove_entity(*SettingsSubLayout);
        SettingsSubLayout.reset();
    }

    if (id == 1) {
        SettingsSubLayout = world().create_entity(
            Parent { this->entity() },
            RectTransform {}
                .set_anchors({ 0.0f, 0.0f }, { 1.0f, 1.0f })
                .set_bounds({ 0.0f, 0.0f }, { 0.0f, 0.0f }),
            Scripts::from(LayoutSubAudio { this->entity() }));
    }
}

bool MenuLayoutManager::execClick()
{
    const std::function<void()> mainActions[]
        = { [&]() { goToSolo(); }, [&]() { layoutID = 5; },
            [&]() { switchSettings(1); }, [&]() { app.quit(); },
            [&]() { layoutID = 4; } };

    const std::function<void()> audioActions[]
        = { [&]() { switchSettings(1); }, [&]() { switchSettings(2); },
            [&]() { switchSettings(3); }, [&]() { switchSettings(0); } };

    const std::function<void()> displayActions[]
        = { [&]() { switchSettings(2); }, [&]() { switchSettings(1); },
            [&]() { switchSettings(3); }, [&]() { switchSettings(0); } };

    const std::function<void()> controlsActions[]
        = { [&]() { switchSettings(3); }, [&]() { switchSettings(2); },
            [&]() { switchSettings(1); }, [&]() { switchSettings(0); } };

    const std::function<void()> helpActions[] = { [&]() { layoutID = 0; } };

    const std::function<void()> multiActions[]
        = { [&]() { layoutID = 6; }, [&]() { goToLocal(); },
            [&]() { layoutID = 0; } };

    const std::function<void()> onlineActions[]
        = { [&]() { goToMultiHost(); }, [&]() { goToMultiJoin(); },
            [&]() { layoutID = 0; } };

    const auto actions
        = { mainActions, audioActions, displayActions, controlsActions,
            helpActions, multiActions, onlineActions };

    auto current = actions.begin() + layoutID;

    if (selectionID >= 10 && !dirty) {
        lockMove = true;
        dirty = false;
        return false;
    } else {
        (*current)[selectionID]();
        dirty = false;
        return true;
    }
}

bool MenuLayoutManager::manageClick(InputManager<>* input)
{
    if (lockMove)
        return false;

    if (input->is_action_down("action") && *input->is_action_down("action")) {
        playSound(audio_valid);
        return execClick();
    }
    return false;
}

bool MenuLayoutManager::manageMove(ige::plugin::input::InputManager<>* input)
{
    if (lockMove)
        return false;

    const auto& currentLayout = layout[layoutID];
    glm::vec2 pos = currentPos();
    glm::vec2 mapSize = currentMapSize();

    auto h = *input->get_axis_value("horizontal");
    auto v = *input->get_axis_value("vertical");

    if (v < 0.0f) {
        pos.y--;
    } else if (v > 0.0f) {
        pos.y++;
    } else if (h > 0.0f) {
        pos.x++;
    } else if (h < 0.0f) {
        pos.x--;
    }

    if (pos.x < 0 || pos.y < 0 || pos.x > mapSize.x || pos.y >= mapSize.y
        || currentLayout[(int)pos.y][(int)pos.x] < 0)
        return false;
    if (selectionID != currentLayout[(int)pos.y][(int)pos.x])
        playSound(audio_move);
    selectionID = currentLayout[(int)pos.y][(int)pos.x];
    return true;
}

void MenuLayoutManager::refreshLayout()
{
    static const Texture::Handle layouts[] = { layout_main_img,
                                               layout_settings_audio_img,
                                               layout_settings_display_img,
                                               layout_settings_controls_img,
                                               layout_help_img,
                                               layout_multi_img,
                                               layout_multi_online_img };

    get_component<ImageRenderer>()->texture = layouts[layoutID];
    selectionID = 0;
}

void MenuLayoutManager::refreshSelection()
{
    const Texture::Handle mainMenuSelect[]
        = { layout_main_selection_solo_img, layout_main_selection_multi_img,
            layout_main_selection_settings_img, layout_main_selection_exit_img,
            layout_main_selection_tuto_img };

    const Texture::Handle settingsMenuAudioSelect[]
        = { layout_settings_selection_side_audio_img,
            layout_settings_selection_side_display_img,
            layout_settings_selection_side_controls_img,
            layout_settings_selection_back_img };

    const Texture::Handle settingsMenuDisplaySelect[]
        = { layout_settings_selection_side_display_img,
            layout_settings_selection_side_audio_img,
            layout_settings_selection_side_controls_img,
            layout_settings_selection_back_img };

    const Texture::Handle settingsMenuControlsSelect[]
        = { layout_settings_selection_side_controls_img,
            layout_settings_selection_side_display_img,
            layout_settings_selection_side_audio_img,
            layout_settings_selection_back_img };

    const Texture::Handle helpMenuSelect[]
        = { layout_settings_selection_back_img };

    const Texture::Handle multiMenuSelect[]
        = { layout_multi_selection_online_img, layout_multi_selection_local_img,
            layout_settings_selection_back_img };

    const Texture::Handle multiMenuOnlineSelect[]
        = { layout_multi_selection_online_host_img,
            layout_multi_selection_online_join_img,
            layout_settings_selection_back_img };

    const Texture::Handle* layoutSelect[] = { mainMenuSelect,
                                              settingsMenuAudioSelect,
                                              settingsMenuDisplaySelect,
                                              settingsMenuControlsSelect,
                                              helpMenuSelect,
                                              multiMenuSelect,
                                              multiMenuOnlineSelect };

    for (auto [ent, block, imageRenderer] :
         world().query<MenuSelectionTag, ImageRenderer>()) {

        if (selectionID < 10)
            imageRenderer.texture = layoutSelect[layoutID][selectionID];
        else
            imageRenderer.texture = nullptr;
    }
}

void MenuLayoutManager::update()
{
    ige::plugin::input::InputManager<>* input = get_resource<InputManager<>>();

    // Add delay between menu movement
    auto now = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = now - action_clock;

    if (elapsed_seconds.count() < 0.1f) {
        return;
    }
    if (manageClick(input)) {
        action_clock = std::chrono::steady_clock::now();
        refreshLayout();
    }
    if (manageMove(input)) {
        action_clock = std::chrono::steady_clock::now();
        refreshSelection();
    }
}

void MenuLayoutManager::tick()
{
}
