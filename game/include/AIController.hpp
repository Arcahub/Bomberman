/*
** EPITECH PROJECT, 2021
** AIController
** File description:
** AIController
*/

#ifndef AICONTROLLER_HPP_
#define AICONTROLLER_HPP_

#include "AStar.hpp"
#include "glm/vec2.hpp"
#include "ige.hpp"

using ige::plugin::script::CppBehaviour;
using ige::plugin::script::ScriptPlugin;
using ige::plugin::script::Scripts;

class AIController : public CppBehaviour {
public:
    AIController(
        std::vector<ige::ecs::EntityId> blockMuds,
        std::vector<glm::vec2> posBlockMuds,
        std::vector<std::vector<int>> mapMaze);
    ~AIController();

    void update() override;

    int m_life = 3;

    glm::vec2 m_direction { 0.0f };

protected:
private:
    std::vector<ige::ecs::EntityId> m_blockMuds;
    std::vector<glm::vec2> m_posBlockMuds;
    std::vector<std::vector<int>> m_mapMaze;

    AStar m_astar;

    float m_speed = 2;
    int m_level = 1;
};

#endif /* !AICONTROLLER_HPP_ */
