#ifndef PLAYERCONTROLLER_HPP_
#define PLAYERCONTROLLER_HPP_

#include "glm/vec2.hpp"
#include "ige.hpp"

using ige::plugin::script::CppBehaviour;
using ige::plugin::script::ScriptPlugin;
using ige::plugin::script::Scripts;

class PlayerController : public CppBehaviour {
public:
    PlayerController() = default;

    PlayerController(
        std::vector<ige::ecs::EntityId> blockMuds,
        std::vector<glm::vec2> posBlockMuds);
    ~PlayerController();

    void tick() override;
    void update() override;

    int m_life = 3;
    float m_speed = 2.5f;
    float m_actionSpeed = 5.0f;
    bool m_reverseControlle = false;

protected:
private:
    void SetEvent();
    void SetMovement(glm::vec2 input);
    void SetAction(bool bomb);

    glm::vec3 rotationSave = { 0, 0, 0 };

    std::vector<ige::ecs::EntityId> m_blockMuds;
    std::vector<glm::vec2> m_posBlockMuds;
    float canAction = 0;

    float reverseCount = 20.0f;

    std::size_t cur_track = 0;
    bool started = false;

    enum class stateAnim { Idle, Run, Attack };
    stateAnim statePlayer = stateAnim::Idle;
};

#endif /* !PLAYERCONTROLLER_HPP_ */
