#include "scripts/CharacterController.hpp"
#include "ige.hpp"
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

using glm::vec2;
using glm::vec3;
using ige::ecs::EntityId;
using ige::plugin::physics::PhysicsWorld;
using ige::plugin::physics::RigidBody;

CharacterController::CharacterController(const EntityId& ground)
    : m_ground(ground)
{
}

void CharacterController::tick()
{
    auto rigidbody = get_component<RigidBody>();
    auto physic_world = get_resource<PhysicsWorld>();

    if (direction != vec2 { 0.0f }) {

        vec2 velocity = glm::normalize(direction) * 2.f;

        if (running) {
            velocity *= 2.0f;
        }
        rigidbody->set_velocity(
            vec3 { velocity.x, rigidbody->velocity().y, velocity.y });
    }

    m_grounded = physic_world->collide(entity(), m_ground);

    if (jump && m_grounded) {
        rigidbody->apply_force(vec3 { 0.0f, 2.0f, 0.0f });
    }
}
