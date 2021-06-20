#ifndef SOLOCONTROLLER_HPP_
#define SOLOCONTROLLER_HPP_

#include "glm/vec2.hpp"
#include "ige.hpp"

using ige::plugin::script::CppBehaviour;
using ige::plugin::script::ScriptPlugin;
using ige::plugin::script::Scripts;

class SoloController : public CppBehaviour {
public:
    SoloController(
        const std::optional<ige::plugin::input::ControllerId>& controller_id
        = std::nullopt);

    void tick() override;

    void SetSoloMovement(ige::plugin::input::InputManager<>* input);

    std::optional<ige::plugin::input::ControllerId> controller_id() const;

    glm::vec2 m_direction { 0.0f };
    bool m_bomb = false;

protected:
private:
    std::optional<ige::plugin::input::ControllerId> m_controller_id;
};

#endif /* !SOLOCONTROLLER_HPP_ */
