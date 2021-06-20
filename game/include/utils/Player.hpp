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
    static ige::ecs::EntityId spawn(
        ige::ecs::World& wld, Bh controller,
        const glm::vec3& pos = glm::vec3 { 0.0f })
    {
        ige::plugin::physics::Collider boxCollider
            = { ige::plugin::physics::ColliderType::BOX };
        boxCollider.box.extents = { 0.25f, 0.25f, 0.25f };

        std::optional<ige::ecs::EntityId> playerRoot;

        auto map_ressources = wld.get<MapRessources>();

        // Set map as parent if map ressources found
        if (map_ressources) {
            playerRoot = wld.create_entity(
                ige::plugin::transform::Transform::from_pos(pos),
                ige::plugin::physics::RigidBody { boxCollider, 10, false },
                PlayerTag {},
                ige::plugin::script::Scripts::from(
                    std::move(controller), PlayerController {}),
                ige::plugin::transform::Parent { map_ressources->map_id });
        } else {
            playerRoot = wld.create_entity(
                ige::plugin::transform::Transform::from_pos(pos),
                ige::plugin::physics::RigidBody { boxCollider, 10, false },
                PlayerTag {},
                ige::plugin::script::Scripts::from(
                    std::move(controller), PlayerController {}));
        }

        wld.create_entity(
            ige::plugin::transform::Transform::from_pos(
                glm::vec3(0.0f, -0.0f, 0.0f))
                .set_scale(0.35f),
            ige::plugin::gltf::GltfScene {
                "assets/Models/player_fixed.glb",
                ige::plugin::gltf::GltfFormat::BINARY,
            },
            ige::plugin::transform::Parent { *playerRoot });

        wld.create_entity(
            ige::plugin::transform::Transform::from_pos(
                glm::vec3(0.0f, 1.5f, 0.0f)),
            ige::plugin::render::Light::point(0.4f),
            ige::plugin::transform::Parent { *playerRoot });
        return *playerRoot;
    }
};

#endif /* BA55D6BE_8617_4EF1_9EB5_624817306471 */
