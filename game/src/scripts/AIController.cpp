/*
** EPITECH PROJECT, 2021
** AIController
** File description:
** AIController
*/

#include "scripts/AIController.hpp"
#include "scripts/Bomb.hpp"

#include <iostream>

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

using glm::vec3;
using glm::vec4;
using ige::asset::Material;
using ige::asset::Mesh;
using ige::core::App;
using ige::core::EventChannel;
using ige::core::State;
using ige::ecs::Schedule;
using ige::ecs::World;
using ige::plugin::input::InputManager;
using ige::plugin::input::KeyboardKey;
using ige::plugin::render::MeshRenderer;
using ige::plugin::time::Time;
using ige::plugin::transform::Transform;

using ige::plugin::physics::Collider;
using ige::plugin::physics::ColliderType;
using ige::plugin::physics::Constraint;
using ige::plugin::physics::PhysicsWorld;
using ige::plugin::physics::RigidBody;

AIController::AIController(
    std::vector<ige::ecs::EntityId> blockMuds,
    std::vector<glm::vec2> posBlockMuds, std::vector<std::vector<int>> mapMaze)
{
    m_blockMuds = blockMuds;
    m_posBlockMuds = posBlockMuds;
    std::vector<std::vector<int>> maze
        = { { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
            { 1, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 1 },
            { 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1 },
            { 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1 },
            { 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1 },
            { 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1 },
            { 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
            { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 } };
    m_mapMaze = mapMaze;

    for (std::vector<int> str : mapMaze) {
        for (int s : str)
            std::cout << s;
        std::cout << std::endl;
    }
    std::cout << std::endl;
    m_astar.InitAStar(maze);
}

AIController::~AIController()
{
}

void AIController::update()
{
    auto xform = get_component<Transform>()->translation();

    if (m_life <= 0) {
        std::cout << m_life << std::endl;
        world().remove_entity(this->entity());
        return;
    }

    m_astar.InitAStar(m_mapMaze);
    Point start(1, 1);
    Point end(6, 10);

    std::list<Point*> path = m_astar.GetPath(start, end, false);
    for (auto& p : path)
        std::cout << '(' << p->x << ',' << p->y << ')' << std::endl;
}
