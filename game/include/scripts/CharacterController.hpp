#ifndef D6EC7F60_FA9A_49F2_B966_28A0EA4055BF
#define D6EC7F60_FA9A_49F2_B966_28A0EA4055BF

#include "ige.hpp"
#include <glm/vec2.hpp>

class CharacterController : public ige::plugin::script::CppBehaviour {
private:
    ige::ecs::EntityId m_ground;
    bool m_grounded = true;

public:
    glm::vec2 direction { 0.0f };
    bool running = false;
    bool jump = false;

    CharacterController(const ige::ecs::EntityId& ground);

    void tick() override;
};

#endif /* D6EC7F60_FA9A_49F2_B966_28A0EA4055BF */
