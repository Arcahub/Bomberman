#ifndef BA55D6BE_8617_4EF1_9EB5_624817306471
#define BA55D6BE_8617_4EF1_9EB5_624817306471

#include "ige.hpp"
#include "scripts/AIController.hpp"
#include "scripts/NetworkController.hpp"
#include "scripts/PlayerController.hpp"
#include "scripts/SoloController.hpp"
#include "utils/Tag.hpp"
#include <glm/vec3.hpp>
#include <iostream>

class Player {
public:
    template <ige::plugin::script::Behaviour Bh>
    static ige::ecs::EntityId
    spawn(ige::ecs::World& wld, const glm::vec3& pos = glm::vec3 { 0.0f })
    {
        std::cout << "SPAWN PLAYER" << std::endl;
        ige::plugin::physics::Collider boxCollider
            = { ige::plugin::physics::ColliderType::BOX };
        boxCollider.box.extents = { 0.25f, 0.25f, 0.25f };

        auto playerRoot = wld.create_entity(
            ige::plugin::transform::Transform::from_pos(pos),
            ige::plugin::physics::RigidBody { boxCollider, 10, false },
            PlayerTag {},
            ige::plugin::script::Scripts::from(Bh {}, PlayerController {}));

        wld.create_entity(
            ige::plugin::transform::Transform::from_pos(
                glm::vec3(0.0f, -0.88f, 0.0f))
                .set_scale(0.35f),
            ige::plugin::gltf::GltfScene {
                "assets/Models/player_fixed.glb",
                ige::plugin::gltf::GltfFormat::BINARY,
            },
            ige::plugin::transform::Parent { playerRoot });
        return playerRoot;
    }
};

#endif /* BA55D6BE_8617_4EF1_9EB5_624817306471 */
