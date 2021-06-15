#include "MysteryBox.hpp"
#include "Tag.hpp"

using ige::ecs::World;
using ige::plugin::physics::Collider;
using ige::plugin::physics::Collision;
using ige::plugin::physics::PhysicsWorld;
using ige::plugin::physics::RigidBody;
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
    auto physic = get_component<PhysicsWorld>();

    xform->rotate(glm::vec3 { 25, 25, 25 } * time->delta_seconds());
    for (auto [ent, block, playerController, posPlayer] :
         world().query<Player, Scripts, Transform>()) {
        if (physic->collide(ent, entity()) == true)
            std::cout << "!" << std::endl;
    }
}
