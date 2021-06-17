#include "scripts/MysteryBox.hpp"
#include "scripts/PlayerController.hpp"
#include "utils/Tag.hpp"

#include <random>

using ige::ecs::World;
using ige::plugin::physics::PhysicsWorld;
using ige::plugin::time::Time;
using ige::plugin::transform::Transform;

MysteryBox::MysteryBox()
{
}

MysteryBox::~MysteryBox()
{
}

void MysteryBox::update()
{
    auto time = world().get<Time>();
    auto xform = get_component<Transform>();
    auto physics_world = world().get<PhysicsWorld>();

    xform->rotate(glm::vec3 { 25, 25, 25 } * time->delta_seconds());

    if (physics_world) {
        for (auto [entPlayer, block, playerController, posPlayer] :
             world().query<Player, Scripts, Transform>()) {
            if (physics_world->collide(entPlayer, entity())) {
                ApplyEffect(playerController);
            }
        }
    }
}

void MysteryBox::ApplyEffect(ige::plugin::script::Scripts& playerController)
{
    srand((int)time(0));
    int result = rand() % 3;
    auto playerControllerScp = playerController.get<PlayerController>();

    switch (result) {
    case 0:
        // good sound
        playerControllerScp->m_speed += 1.0f;
        break;
    case 1:
        // maluss sound
        playerControllerScp->m_reverseControlle = true;
        break;
    default:
        // good sound
        playerControllerScp->m_actionSpeed -= 1.0f;
        break;
    }

    world().remove_entity(entity());
}
