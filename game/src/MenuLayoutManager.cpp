#include "MenuLayoutManager.hpp"
#include "RootState.hpp"
#include "Tag.hpp"
#include <functional>

using ige::ecs::World;
using ige::plugin::input::InputManager;
using ige::plugin::render::ImageRenderer;
using ige::plugin::time::Time;
using ige::plugin::transform::Transform;

// Menu layout const data

static const int main_menu_map[3][4]
    = { { 4, 0, 1, -2 }, { -1, 2, 3, -2 }, { -3, -3, -3, -3 } };

static const int (*layout[])[4] = { main_menu_map };

// Menu Layout Manager

MenuLayoutManager::MenuLayoutManager(
    Texture::Handle layout_start, ige::core::App& app)
    : m_app(app)
{
    layout_main_selection_solo_img = layout_start;
}

MenuLayoutManager::~MenuLayoutManager()
{
}

void MenuLayoutManager::on_start()
{
    layout_main_selection_multi_img
        = Texture::make_new("assets/Menu/Bomb/Menus/Main/Menu_main_multi.png");
    layout_main_selection_settings_img = Texture::make_new(
        "assets/Menu/Bomb/Menus/Main/Menu_main_settings.png");
    layout_main_selection_exit_img
        = Texture::make_new("assets/Menu/Bomb/Menus/Main/Menu_main_exit.png");
    layout_main_selection_tuto_img
        = Texture::make_new("assets/Menu/Bomb/Menus/Main/Menu_main_tuto.png");
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
    /*for (auto ent : world().remove_entity()) {

        imageRenderer.texture = layoutSelect[layoutID][selectionID];
    }*/

    m_app.state_machine().switch_to<RootState>();
}

void MenuLayoutManager::execClick()
{
    if (layoutID == 0) {

        switch (selectionID) {
        case 0:
            goToGame();
            break;
        case 1:
            /* code */
            break;
        case 2:
            /* code */
            break;
        case 3:
            m_app.quit();
            break;
        case 4:
            /* code */
            break;
        default:
            break;
        }

    } else if (layoutID == 1) {
    }
}

bool MenuLayoutManager::manageClick(ige::plugin::input::InputManager* input)
{
    if (input->keyboard().is_pressed(KeyboardKey::KEY_SPACE)) {
        execClick();
        return true;
    }
    return false;
}

bool MenuLayoutManager::manageMove(ige::plugin::input::InputManager* input)
{
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

    std::cout << pos.x << " ; " << pos.y << std::endl;

    if (pos.x < 0 || pos.y < 0 || pos.x > mapSize.x || pos.y >= mapSize.y
        || currentLayout[(int)pos.y][(int)pos.x] < 0)
        return false;

    std::cout << currentLayout[(int)pos.y][(int)pos.x] << std::endl;

    selectionID = currentLayout[(int)pos.y][(int)pos.x];
    return true;
}

void MenuLayoutManager::refreshLayout()
{
}

void MenuLayoutManager::refreshSelection()
{
    static const Texture::Handle mainMenuSelect[]
        = { layout_main_selection_solo_img, layout_main_selection_multi_img,
            layout_main_selection_settings_img, layout_main_selection_exit_img,
            layout_main_selection_tuto_img };

    static const Texture::Handle* layoutSelect[] = { mainMenuSelect };

    for (auto [ent, block, imageRenderer] :
         world().query<MenuSelection, ImageRenderer>()) {

        imageRenderer.texture = layoutSelect[layoutID][selectionID];
    }
}

void MenuLayoutManager::update()
{
}

void MenuLayoutManager::tick()
{
    ige::plugin::input::InputManager* input = get_resource<InputManager>();

    if (manageClick(input)) {
        refreshLayout();
    }

    if (manageMove(input)) {
        refreshSelection();
    }
}
