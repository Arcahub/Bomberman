#include "scripts/AIController.hpp"
#include "scripts/Bomb.hpp"
#include "utils/Tag.hpp"

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
    std::vector<glm::vec2> posBlockMuds, std::vector<std::vector<int>> mapMaze,
    std::vector<std::vector<int>> mapMazeEvent)
{
    m_blockMuds = blockMuds;
    m_posBlockMuds = posBlockMuds;
    m_mapMaze = mapMaze;
    m_mapMazeEvent = mapMazeEvent;
    sizeMap.x = mapMaze[0].size();
    sizeMap.y = mapMaze.size();

    /*for (std::vector<int> str : mapMaze) {
        for (int s : str)
            std::cout << s;
        std::cout << std::endl;
    }
    std::cout << std::endl;*/
    m_astar.InitAStar(m_mapMaze);
}

void AIController::update()
{
    // auto xform = get_component<Transform>()->translation();
    // glm::vec3 posBomb;
    // bool isAction = false;

    // if (m_life <= 0) {
    //     std::cout << m_life << std::endl;
    //     world().remove_entity(this->entity());
    //     return;
    // }
    // if (spawnBomb == true && timerBomb <= 0)
    //     spawnBomb = false;
    // else
    //     timerBomb -= get_resource<Time>()->delta_seconds();

    // for (auto [ent, block, playerController, posPlayer] :
    //      world().query<PlayerTag, Scripts, Transform>()) {
    //     auto pos = posPlayer.world_translation();

    //     Point start(
    //         glm::round(xform.x + (sizeMap.x / 2)),
    //         glm::round(xform.z + (sizeMap.y / 2)));
    //     Point end(
    //         glm::round(pos.x + (sizeMap.x / 2)),
    //         glm::round(pos.z + (sizeMap.y / 2)));

    //     /*std::cout << "! " << glm::round(pos.x + (sizeMap.x / 2)) << " "
    //               << glm::round(pos.z + (sizeMap.y / 2)) << std::endl;
    //     std::cout << "? " << glm::round(xform.x + (sizeMap.x / 2)) << " "
    //               << glm::round(xform.z + (sizeMap.y / 2)) << std::endl;

    //     std::cout << start.x << " " << start.y << std::endl;
    //     std::cout << end.x << " " << end.y << std::endl;*/
    //     std::list<Point*> path = m_astar.GetPath(start, end, false);

    //     if (glm::distance(xform, pos) <= 1.5f) {
    //         m_bomb = true;
    //         spawnBomb = true;
    //     } else
    //         m_bomb = false;

    //     /*if (path.size() == 0) {
    //         Point *point = pos.x, pos.z;
    //         path.push_front(point);
    //     }*/
    //     pathNumber = 0;
    //     for (auto& p : path) {
    //         if (stepAI != pathNumber)
    //             continue;
    //         m_direction = { 0.0f, 0.0f };

    //         if (firstLoop == false)
    //             pStart = { p->x, p->y };
    //         firstLoop = true;

    //         for (auto [ent, block, posBombs] :
    //              world().query<BombTag, Transform>()) {
    //             posBomb = posBombs.world_translation();
    //             glm::vec3 pathPos = { p->x, posBomb.y, p->y };

    //             if (spawnBomb == true) {
    //                 isAction = true;
    //                 if (pStart.y > posBomb.z)
    //                     m_direction.y += 0.5f;
    //                 else if (pStart.y < posBomb.z)
    //                     m_direction.y -= 0.5f;
    //                 if (pStart.x > posBomb.x)
    //                     m_direction.x += 0.5f;
    //                 else if (pStart.x < posBomb.x)
    //                     m_direction.x -= 0.5f;
    //             }

    //             // si il y a une bombe il recule
    //             /*if (glm::distance(pathPos, pos)
    //                 > glm::distance(pathPos, posBomb)) {
    //                 isAction = true;
    //                 if (p->y > posBomb.z)
    //                     m_direction.y -= 0.5f;
    //                 else if (p->y < posBomb.z)
    //                     m_direction.y += 0.5f;
    //                 if (p->x > posBomb.x)
    //                     m_direction.x -= 0.5f;
    //                 else if (p->x < posBomb.x)
    //                     m_direction.x += 0.5f;
    //             }*/
    //         }
    //         if (isAction == true) {
    //             pathNumber++;
    //             break;
    //         }
    //         // isAction = true;

    //         // std::cout << '(' << p->x << ',' << p->y << ')' << std::endl;
    //         if (m_mapMazeEvent[p->y][p->x - 1] == 2) {
    //             std::cout << "x = " << xform.x << " y = " << xform.z
    //                       << std::endl;
    //             std::cout << "x = " << p->x << " y = " << p->y << std::endl;
    //             if (glm::distance(
    //                     glm::vec2 { p->x, 0 }, glm::vec2 { xform.x, 0 })
    //                     < 1.75f
    //                 && glm::distance(
    //                        glm::vec2 { p->y, 0 }, glm::vec2 { xform.z, 0 })
    //                     < 1.75f) {
    //                 m_bomb = true;
    //                 spawnBomb = true;
    //             }
    //         }

    //         if (p->y > start.y)
    //             m_direction.y += 0.5f;
    //         else if (p->y < start.y)
    //             m_direction.y -= 0.5f;
    //         if (p->x > start.x)
    //             m_direction.x += 0.5f;
    //         else if (p->x < start.x)
    //             m_direction.x -= 0.5f;

    //         // si il y a une bombe il rebrousse chemain maisssss a voir
    //         // if (m_bomb == true)
    //         //    m_direction = { m_direction.x * -1, m_direction.y * -1 };
    //         pathNumber++;
    //     }
    // }
}
