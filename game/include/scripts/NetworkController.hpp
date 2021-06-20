#ifndef E98C08FE_C6F6_43D1_931C_8BF4A5A5BC51
#define E98C08FE_C6F6_43D1_931C_8BF4A5A5BC51

#include "ige.hpp"
#include <unordered_map>

class NetworkController : public ige::plugin::script::CppBehaviour {
public:
    enum Action { LEFT, RIGHT, UP, DOWN, BOMB };

    enum ActionUpdateStates {
        LEFT_PRESSED,
        LEFT_RELEASED,
        RIGHT_PRESSED,
        RIGHT_RELEASED,
        UP_PRESSED,
        UP_RELEASED,
        DOWN_PRESSED,
        DOWN_RELEASED,
        BOMB_ACTION
    };

    std::vector<ActionUpdateStates> update_states;
    std::unordered_map<Action, bool> actions;
    void tick() override;

    glm::vec2 m_direction { 0.0f };
    bool m_bomb = false;
};

#endif /* E98C08FE_C6F6_43D1_931C_8BF4A5A5BC51 */
