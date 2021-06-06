//
// Created by mathias on 6/2/21.
//

#ifndef BOMBERMAN_BOMB_HPP
#define BOMBERMAN_BOMB_HPP

#include "ige.hpp"

using ige::plugin::script::CppBehaviour;
using ige::plugin::script::ScriptPlugin;
using ige::plugin::script::Scripts;

class Bomb : public CppBehaviour {
public:
    Bomb(
        std::vector<ige::ecs::EntityId> blockMuds,
        std::vector<glm::vec2> posBlockMuds);
    ~Bomb();

    void on_start() override;
    void update() override;

protected:
private:
    std::vector<ige::ecs::EntityId> m_blockMuds;
    std::vector<glm::vec2> m_posBlockMuds;

    float explosed = 5.0f;
    bool isDone = false;
};

#endif // BOMBERMAN_BOMB_HPP
