#ifndef PLAYERCONTROLLER_HPP_
#define PLAYERCONTROLLER_HPP_

#include "glm/vec2.hpp"
#include "ige.hpp"
#include "scripts/TrackballCamera.hpp"

using ige::plugin::script::CppBehaviour;
using ige::plugin::script::ScriptPlugin;
using ige::plugin::script::Scripts;

class PlayerController : public CppBehaviour {
public:
    void update() override;

    int m_life = 3;
    int m_life_ui = m_life;
    int m_rangeBomb = 0;
    float m_speed = 2.5f;
    float m_actionSpeed = 5.0f;
    float reverseCamCount = 0.0f;
    bool m_reverseControlle = false;
    bool m_reverseCam = false;

    TrackballCamera* cam;

protected:
private:
    void SetEvent();
    void SetMovement(glm::vec2 input);
    void SetAction(bool bomb, glm::vec2 direction);

    glm::vec3 rotationSave = { 0, 0, 0 };
    glm::vec2 directionSave = { 0.0f, 0.0f };

    int m_id = -1;
    float canAction = 0;

    float reverseCount = 20.0f;

    std::size_t cur_track = 0;
    bool started = false;
    bool gameIsStart = false;

    enum class stateAnim { Idle, Run, Attack };
    stateAnim statePlayer = stateAnim::Idle;
};

#endif /* !PLAYERCONTROLLER_HPP_ */
