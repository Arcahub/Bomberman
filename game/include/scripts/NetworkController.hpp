#ifndef E98C08FE_C6F6_43D1_931C_8BF4A5A5BC51
#define E98C08FE_C6F6_43D1_931C_8BF4A5A5BC51

#include "ige.hpp"
#include <unordered_map>

class NetworkController : public ige::plugin::script::CppBehaviour {
public:
    enum Actions { LEFT, RIGHT, UP, DOWN, BOMB };

    std::vector<Actions> actions;
    void tick() override;

    glm::vec2 m_direction { 0.0f };
    bool m_bomb = false;
};

#endif /* E98C08FE_C6F6_43D1_931C_8BF4A5A5BC51 */
