#ifndef MENULAYOUTMANAGER_HPP_
#define MENULAYOUTMANAGER_HPP_

#include "ige.hpp"
#include <glm/vec3.hpp>

using ige::asset::Texture;
using ige::core::App;
using ige::plugin::audio::AudioClip;
using ige::plugin::audio::AudioListener;
using ige::plugin::audio::AudioSource;
using ige::plugin::input::InputManager;
using ige::plugin::input::KeyboardKey;
using ige::plugin::script::CppBehaviour;
using ige::plugin::script::ScriptPlugin;
using ige::plugin::script::Scripts;

class MenuLayoutManager : public CppBehaviour {
public:
    MenuLayoutManager(
        Texture::Handle layout_start, Texture::Handle layout_select, App& app);
    ~MenuLayoutManager();

    void update() override;
    void on_start() override;
    void tick() override;

    bool lockMove = false;
    int selectionID = 0;

protected:
private:
    // inside method
    void playSound(std::shared_ptr<ige::plugin::audio::AudioClip> ac);
    bool manageClick(ige::plugin::input::InputManager<>* input);
    bool manageMove(ige::plugin::input::InputManager<>* input);
    void refreshLayout();
    void refreshSelection();
    bool execClick();
    void goToSolo();
    void goToLocal();
    void goToMultiHost();
    void goToMultiJoin();
    void switchSettings(int id);
    glm::vec2 currentPos();
    glm::vec2 currentMapSize();

    // Atribut
    int layoutID = 0;
    ige::core::App& app;
    std::optional<ige::ecs::EntityId> SettingsSubLayout;

    // === AUDIO ===

    std::shared_ptr<AudioClip> audio_wrong;
    std::shared_ptr<AudioClip> audio_valid;
    std::shared_ptr<AudioClip> audio_move;
    std::optional<ige::ecs::EntityId> audioSource;

    // === SPRITES ===

    // == LAYOUT ==
    Texture::Handle layout_main_img;
    Texture::Handle layout_settings_audio_img;
    Texture::Handle layout_settings_display_img;
    Texture::Handle layout_settings_controls_img;
    Texture::Handle layout_multi_img;
    Texture::Handle layout_multi_online_img;
    Texture::Handle layout_help_img;

    // == SELECTION ==
    // main menu sprites
    Texture::Handle layout_main_selection_solo_img;
    Texture::Handle layout_main_selection_multi_img;
    Texture::Handle layout_main_selection_settings_img;
    Texture::Handle layout_main_selection_exit_img;
    Texture::Handle layout_main_selection_tuto_img;
    // settings menu sprites
    Texture::Handle layout_settings_selection_back_img;
    Texture::Handle layout_settings_selection_side_audio_img;
    Texture::Handle layout_settings_selection_side_controls_img;
    Texture::Handle layout_settings_selection_side_display_img;
    // multi menu sprites
    Texture::Handle layout_multi_selection_online_img;
    Texture::Handle layout_multi_selection_local_img;
    // multi online menu sprites
    Texture::Handle layout_multi_selection_online_host_img;
    Texture::Handle layout_multi_selection_online_join_img;
    // multi online menu sprites
    Texture::Handle layout_settings_help_img;
};

#endif /* !MENULAYOUTMANAGER_HPP_ */