#ifndef LAYOUTSUBCONTROLS_HPP_
#define LAYOUTSUBCONTROLS_HPP_

#include "ige.hpp"
#include "menu/MenuLayoutManager.hpp"

#include <glm/vec3.hpp>

using ige::asset::Texture;
using ige::core::EventChannel;
using ige::plugin::input::InputEvent;
using ige::plugin::input::InputEventType;
using ige::plugin::input::InputManager;
using ige::plugin::input::InputRegistryState;
using ige::plugin::script::CppBehaviour;
using ige::plugin::script::ScriptPlugin;
using ige::plugin::script::Scripts;

class LayoutSubControls : public CppBehaviour {
public:
    LayoutSubControls(std::optional<ige::ecs::EntityId> lm);
    ~LayoutSubControls();

    void update() override;
    void on_start() override;

protected:
private:
    std::optional<EventChannel<InputEvent>::Subscription> m_input_events;
    ige::ecs::EntityId
    createSprite(glm::vec2 anchorMin, glm::vec2 anchorMax, Texture::Handle tex);
    void updateCases(MenuLayoutManager* lm);
    void unlock(MenuLayoutManager* lm);
    void updateActions(MenuLayoutManager* lm);
    Texture::Handle tex_cases;
    Texture::Handle tex_select;
    Texture::Handle tex_valid;
    std::optional<ige::ecs::EntityId> ent_cases[4][5];
    std::optional<ige::ecs::EntityId> layoutManager;
};

#endif /* !LAYOUTSUBCONTROLS_HPP_ */
