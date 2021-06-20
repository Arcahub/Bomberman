#ifndef AICONTROLLER_HPP_
#define AICONTROLLER_HPP_

#include "glm/vec2.hpp"
#include "ige.hpp"

using ige::plugin::script::CppBehaviour;
using ige::plugin::script::ScriptPlugin;
using ige::plugin::script::Scripts;

class AIController : public CppBehaviour {
public:
    AIController() = default;

    void update() override;

    int m_life = 3;

    glm::vec2 m_direction { 0.0f };
    bool m_bomb = false;

protected:
private:
    float timerBomb = 0.0f;
    bool spawnBomb = false;

    float m_speed = 2;
    int m_level = 1;
};

#endif /* !AICONTROLLER_HPP_ */
