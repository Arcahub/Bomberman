#include "scripts/MysteryBox.hpp"
#include "scripts/PlayerController.hpp"
#include "scripts/TrackballCamera.hpp"
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
    int result = rand() % 4;
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
    case 2:
        // maluss sound
        for (auto [ent, block, camController] : world().query<Cam, Scripts>()) {
            auto cam = camController.get<TrackballCamera>();

            cam->m_distance = 12.5f;
            cam->m_theta = -2.3946f;
            cam->m_phi = 1.4981f;
            // Scripts::from(TrackballCamera { 12.5f, -2.3946f, 1.4981f }));
        }
        break;
    default:
        // good sound
        playerControllerScp->m_actionSpeed -= 1.0f;
        break;
    }

    world().remove_entity(entity());
}
