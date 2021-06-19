#include "menu/MenuLayoutManager.hpp"
#include "menu/LayoutSubAudio.hpp"
#include "menu/LayoutSubControls.hpp"
#include "menu/LayoutSubDisplay.hpp"
#include "states/PreSoloGameState.hpp"
#include "states/RoomState.hpp"
#include "utils/Tag.hpp"
#include <functional>

using ige::ecs::World;
using ige::plugin::input::InputManager;
using ige::plugin::render::ImageRenderer;
using ige::plugin::time::Time;
using ige::plugin::transform::Parent;
using ige::plugin::transform::RectTransform;
using ige::plugin::transform::Transform;

// Menu layout map data

static const int main_menu_map[3][4]
    = { { 4, 0, 1, -2 }, { -1, 2, 3, -2 }, { -3, -3, -3, -3 } };

static const int settings_menu_audio_map[4][4] = {
    { 3, 0, 10, -2 }, { 3, 1, 11, -2 }, { 3, 2, 12, -2 }, { -3, -3, -3, -3 }
};

static const int settings_menu_display_map[4][4] = {
    { 3, 1, -2, -2 }, { 3, 0, -2, -2 }, { 3, 2, -2, -2 }, { -3, -3, -3, -3 }
};

static const int settings_menu_controls_map[4][4] = {
    { 3, 2, -2, -2 }, { 3, 1, -2, -2 }, { 3, 0, -2, -2 }, { -3, -3, -3, -3 }
};

static const int (*layout[])[4]
    = { main_menu_map, settings_menu_audio_map, settings_menu_display_map,
        settings_menu_controls_map };

// Menu Layout Manager

MenuLayoutManager::MenuLayoutManager(
    Texture::Handle layout_start, Texture::Handle layout_select,
    ige::core::App& app)
    : app(app)
{
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

void MenuLayoutManager::goToGame()
{
    app.state_machine().switch_to<PreSoloGameState>();
}

void MenuLayoutManager::goToMulti()
{
    app.state_machine().switch_to<RoomState>();
}

void MenuLayoutManager::switchSettings(int id)
{
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
    } else if (id == 2) {
        SettingsSubLayout = world().create_entity(
            Parent { this->entity() },
            RectTransform {}
                .set_anchors({ 0.0f, 0.0f }, { 1.0f, 1.0f })
                .set_bounds({ 0.0f, 0.0f }, { 0.0f, 0.0f }),
            Scripts::from(LayoutSubDisplay {}));
    } else if (id == 3) {
        SettingsSubLayout = world().create_entity(
            Parent { this->entity() },
            RectTransform {}
                .set_anchors({ 0.0f, 0.0f }, { 1.0f, 1.0f })
                .set_bounds({ 0.0f, 0.0f }, { 0.0f, 0.0f }),
            Scripts::from(LayoutSubControls {}));
    }
}

bool MenuLayoutManager::execClick()
{
    const std::function<void()> mainActions[]
        = { [&]() { goToGame(); }, [&]() { goToMulti(); },
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

    const auto actions
        = { mainActions, audioActions, displayActions, controlsActions };

    auto current = actions.begin() + layoutID;

    if (selectionID >= 10) {
        lockMove = true;
        return false;
    } else {
        (*current)[selectionID]();
        return true;
    }
}

bool MenuLayoutManager::manageClick(InputManager<>* input)
{
    if (lockMove)
        return false;

    if (input->keyboard().is_pressed(KeyboardKey::KEY_SPACE)) {
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

    if (input->keyboard().is_pressed(KeyboardKey::KEY_ARROW_UP))
        pos.y--;
    if (input->keyboard().is_pressed(KeyboardKey::KEY_ARROW_DOWN))
        pos.y++;
    if (input->keyboard().is_pressed(KeyboardKey::KEY_ARROW_RIGHT))
        pos.x++;
    if (input->keyboard().is_pressed(KeyboardKey::KEY_ARROW_LEFT))
        pos.x--;
    if (pos.x < 0 || pos.y < 0 || pos.x > mapSize.x || pos.y >= mapSize.y
        || currentLayout[(int)pos.y][(int)pos.x] < 0)
        return false;
    selectionID = currentLayout[(int)pos.y][(int)pos.x];
    return true;
}

void MenuLayoutManager::refreshLayout()
{
    static const Texture::Handle layouts[]
        = { layout_main_img, layout_settings_audio_img,
            layout_settings_display_img, layout_settings_controls_img };

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

    const Texture::Handle* layoutSelect[]
        = { mainMenuSelect, settingsMenuAudioSelect, settingsMenuDisplaySelect,
            settingsMenuControlsSelect };

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
}

void MenuLayoutManager::tick()
{
    ige::plugin::input::InputManager<>* input = get_resource<InputManager<>>();

    if (manageClick(input)) {
        refreshLayout();
    }

    if (manageMove(input)) {
        refreshSelection();
    }
}
