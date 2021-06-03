/*
** EPITECH PROJECT, 2021
** PlayerController
** File description:
** PlayerController
*/

#ifndef PLAYERCONTROLLER_HPP_
#define PLAYERCONTROLLER_HPP_

#include "ige.hpp"

using ige::plugin::script::CppBehaviour;
using ige::plugin::script::ScriptPlugin;
using ige::plugin::script::Scripts;

class PlayerController : public CppBehaviour {
public:
    PlayerController(
        std::vector<ige::ecs::EntityId> blockMuds,
        std::vector<glm::vec2> posBlockMuds);
    ~PlayerController();

    void tick() override;
    void update() override;

protected:
private:
    void SetEvent();
    void SetMovement(auto);
    void SetAction(auto);

    std::vector<ige::ecs::EntityId> m_blockMuds;
    std::vector<glm::vec2> m_posBlockMuds;
    float canAction = 0;

    int m_life = 3;
};

#endif /* !PLAYERCONTROLLER_HPP_ */
