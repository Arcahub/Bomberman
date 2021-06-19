#ifndef MENULAYOUTMANAGER_HPP_
#define MENULAYOUTMANAGER_HPP_

#include "ige.hpp"
#include <glm/vec3.hpp>

using ige::asset::Texture;
using ige::core::App;
using ige::plugin::input::InputManager;
using ige::plugin::input::KeyboardKey;
using ige::plugin::script::CppBehaviour;
using ige::plugin::script::ScriptPlugin;
using ige::plugin::script::Scripts;

class MenuLayoutManager : public CppBehaviour {
public:
    MenuLayoutManager(Texture::Handle layout_start, App& app);
    ~MenuLayoutManager();

    void update() override;
    void on_start() override;
    void tick() override;

protected:
private:
    bool manageClick(ige::plugin::input::InputManager<>* input);
    bool manageMove(ige::plugin::input::InputManager<>* input);
    void refreshLayout();
    void refreshSelection();
    void execClick();
    void goToGame();
    void goToMulti();
    glm::vec2 currentPos();
    glm::vec2 currentMapSize();
    int layoutID = 0;
    int selectionID = 0;
    Texture::Handle layout_main_selection_solo_img;
    Texture::Handle layout_main_selection_multi_img;
    Texture::Handle layout_main_selection_settings_img;
    Texture::Handle layout_main_selection_exit_img;
    Texture::Handle layout_main_selection_tuto_img;
    ige::core::App& m_app;
};

#endif /* !MENULAYOUTMANAGER_HPP_ */
