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

AIController::AIController(int id)
    : m_id(id)
{
}

void AIController::update()
{
    auto xform = get_component<Transform>()->translation();
    glm::vec3 posBomb;
    bool isAction = false;
    bool onDiffPlayer = false;
    std::vector<glm::vec2> diffVec {};

    if (m_life <= 0) {
        std::cout << m_life << std::endl;
        world().remove_entity(this->entity());
        return;
    }
    if (timerBomb <= 0)
        spawnBomb = false;
    else
        timerBomb -= get_resource<Time>()->delta_seconds();

    for (auto [ent, block, playerController, posPlayer] :
         world().query<PlayerTag, Scripts, Transform>()) {
        auto pos = posPlayer.world_translation();

        if (glm::distance(xform, pos) <= 1.5f) {
            m_bomb = true;
            spawnBomb = true;
        } else
            m_bomb = false;

        for (auto [ent, block, posblock] :
             world().query<BreakableBlockTag, Transform>()) {
            auto blockPos = posblock.world_translation();
            float diffX = xform.x - blockPos.x;
            float diffZ = xform.z - blockPos.z;

            if (diffX < 1.25f && diffX > -1.25f && diffZ < 1.25f
                && diffZ > -1.25f) {
                // Y'a un block cassable a coté de lui
                m_bomb = true;
                spawnBomb = true;
            } else {
                // Y'a pas de block cassable a coté de lui
            }
        }

        for (auto [ent, block, posblock] :
             world().query<BlockTag, Transform>()) {
            auto blockPos = posblock.world_translation();
            float diffX = xform.x - blockPos.x;
            float diffZ = xform.z - blockPos.z;

            if (diffX < 0.75f && diffX > -0.75f && diffZ < 0.75f
                && diffZ > -0.75f) {
                isAction = true;
                // Y'a un block a coté de lui
                if (diffX > -0.75f && diffX < 0.0f)
                    m_direction.x = -1.0f;
                if (diffX > 0.0f && diffX < 0.75f)
                    m_direction.x = 1.0f;
                if (diffZ > -0.75f && diffZ < 0.0f)
                    m_direction.y = -1.0f;
                if (diffZ > 0.0f && diffZ < 0.75f)
                    m_direction.y = 1.0f;
            } else if (
                diffX < 1.0f && diffX > -1.0f && diffZ < 1.0f
                && diffZ > -1.0f) {
                // Y'a un block a coté de lui
                if (diffX > -1.0f && diffX < 0.0f)
                    m_direction.x = -1.0f;
                if (diffX > 0.0f && diffX < 1.0f)
                    m_direction.x = 1.0f;
                if (diffZ > -1.0f && diffZ < 0.0f)
                    m_direction.y = -1.0f;
                if (diffZ > 0.0f && diffZ < 1.0f)
                    m_direction.y = 1.0f;
            } else if (isAction == false) {
                // Y'a pas de block a coté de lui
                float diffPlayerX = xform.x - pos.x;
                float diffPlayerZ = xform.z - pos.z;

                /*diffVec.push_back(glm::vec2 { diffPlayerX, diffPlayerZ });
                if (isAction == false)
                    onDiffPlayer = true;*/
                if (spawnBomb) {
                    if (diffPlayerX < 0.0f)
                        m_direction.x = 1.0f;
                    if (diffPlayerX > 0.0f)
                        m_direction.x = -1.0f;
                    if (diffPlayerZ < 0.0f)
                        m_direction.y = 1.0f;
                    if (diffPlayerZ > 0.0f)
                        m_direction.y = -1.0f;
                } else {
                    if (diffPlayerX < 0.0f)
                        m_direction.x = -1.0f;
                    if (diffPlayerX > 0.0f)
                        m_direction.x = 1.0f;
                    if (diffPlayerZ < 0.0f)
                        m_direction.y = -1.0f;
                    if (diffPlayerZ > 0.0f)
                        m_direction.y = 1.0f;
                }
            }
        }
    }

    /*if (onDiffPlayer && isAction == false) {
        int j = 0;
        float diff = 9999999;

        for (int i = 0; i >= diffVec.size(); i++) {
            if (glm::distance(glm::vec2 { xform.x, xform.z }, diffVec[i])
                < diff) {
                diff
                    = glm::distance(glm::vec2 { xform.x, xform.z }, diffVec[i]);
                j = i;
            }
        }
        if (diffVec[j].x < 0.0f)
            m_direction.x = 1.0f;
        if (diffVec[j].x > 0.0f)
            m_direction.x = -1.0f;
        if (diffVec[j].y < 0.0f)
            m_direction.y = 1.0f;
        if (diffVec[j].y > 0.0f)
            m_direction.y = -1.0f;
    }*/
}
