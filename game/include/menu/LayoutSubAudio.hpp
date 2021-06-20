#ifndef LAYOUTSUBAUDIO_HPP_
#define LAYOUTSUBAUDIO_HPP_

#include "ige.hpp"

#include <glm/vec3.hpp>

using ige::asset::Texture;
using ige::plugin::script::CppBehaviour;
using ige::plugin::script::ScriptPlugin;
using ige::plugin::script::Scripts;

class LayoutSubAudio : public CppBehaviour {
public:
    LayoutSubAudio(std::optional<ige::ecs::EntityId> lm);
    ~LayoutSubAudio();

    void update() override;
    void on_start() override;

protected:
private:
    void setBarTexture(int id, std::optional<ige::ecs::EntityId> ent);
    void updateBarsAction(int id);
    void updateBarAction(float& data);
    // entities
    std::optional<ige::ecs::EntityId> audioBar;
    std::optional<ige::ecs::EntityId> musicBar;
    std::optional<ige::ecs::EntityId> fxBar;
    std::optional<ige::ecs::EntityId> audioBarFill;
    std::optional<ige::ecs::EntityId> musicBarFill;
    std::optional<ige::ecs::EntityId> fxBarFill;

    // settings audio menu sprites
    Texture::Handle layout_settings_selection_audio_audio_icon;
    Texture::Handle layout_settings_selection_audio_music_icon;
    Texture::Handle layout_settings_selection_audio_fx_icon;
    Texture::Handle layout_settings_selection_audio_bar;
    Texture::Handle layout_settings_selection_audio_bar_select;
    Texture::Handle layout_settings_selection_audio_bar_valid;
    Texture::Handle layout_settings_selection_audio_bar_fill;

    std::optional<ige::ecs::EntityId> layoutManager;

    float wait = -1;
    float startWait = -1;
};

#endif /* !LAYOUTSUBAUDIO_HPP_ */
