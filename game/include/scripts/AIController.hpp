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
        std::vector<std::vector<int>> mapMaze,
        std::vector<std::vector<int>> mapMazeEvent);
    ~AIController();

    void update() override;

    int m_life = 3;

    glm::vec2 m_direction { 0.0f };
    bool m_bomb = false;

protected:
private:
    std::vector<ige::ecs::EntityId> m_blockMuds;
    std::vector<glm::vec2> m_posBlockMuds;
    std::vector<std::vector<int>> m_mapMaze;
    std::vector<std::vector<int>> m_mapMazeEvent;

    AStar m_astar;
    glm::vec2 pStart = { 0.0f, 0.0f };
    bool firstLoop = false;
    int pathNumber = 0;
    int stepAI = 0;

    float timerBomb = 0.0f;
    bool spawnBomb = false;

    glm::vec2 sizeMap = { -1.0f, -1.0f };
    float m_speed = 2;
    int m_level = 1;
};

#endif /* !AICONTROLLER_HPP_ */
