#include "Player.hpp"
#include "ige.hpp"
#include "scripts.hpp"
#include <glm/vec3.hpp>

using glm::vec3;
using ige::asset::Material;
using ige::asset::Mesh;
using ige::ecs::EntityId;
using ige::ecs::World;
using ige::plugin::physics::Collider;
using ige::plugin::physics::ColliderType;
using ige::plugin::physics::RigidBody;
using ige::plugin::render::MeshRenderer;
using ige::plugin::script::Scripts;
using ige::plugin::transform::Transform;

EntityId Player::generate(World& wld, const PlayerInfo& info)
{
    Collider box_collider = { ColliderType::BOX };
    box_collider.box.extents = { 1.0f, 1.0f, 1.0f };
    auto cube_mesh = Mesh::make_cube(1.0f);

    return wld.create_entity(
        RigidBody { box_collider }, Transform::from_pos({ 0.0f, 0.5f, 0.0f }),
        MeshRenderer {
            cube_mesh,
            Material::make_default(),
        },
        Scripts::from(CharacterController {}));
}
