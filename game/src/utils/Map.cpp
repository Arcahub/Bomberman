#include "utils/Map.hpp"
#include "ige.hpp"
#include "scripts/AIController.hpp"
#include "scripts/PlayerController.hpp"
#include "scripts/SoloController.hpp"
#include "utils/CsvUtils.hpp"
#include "utils/Tag.hpp"

#include <fstream>
#include <iostream>
#include <sstream>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

using glm::vec2;
using glm::vec3;
using ige::asset::Material;
using ige::asset::Mesh;
using ige::ecs::EntityId;
using ige::ecs::World;
using ige::plugin::gltf::GltfFormat;
using ige::plugin::gltf::GltfScene;
using ige::plugin::render::MeshRenderer;
using ige::plugin::transform::Parent;
using ige::plugin::transform::Transform;

using ige::plugin::physics::Collider;
using ige::plugin::physics::ColliderType;
using ige::plugin::physics::RigidBody;

void Map::InitMap(World& wld)
{
    // Generate Map root entity
    auto mapEntity = wld.create_entity(
        Transform::from_pos(glm::vec3 { -3.5f, 0.0f, -3.5f }));
    wld.emplace<MapRessources>(mapEntity);

    Collider boxColliderGround = { ColliderType::BOX };
    boxColliderGround.box.extents = { 2.0f, 0.5f, 2.0f };
    Collider boxCollider = { ColliderType::BOX };
    boxCollider.box.extents = { 2.0f, 2.0f, 2.0f };

    float width = 15.0f;
    float height = 15.0f;

    // Generate background
    wld.create_entity(
        Transform {}
            .set_translation(vec3 { 7.0f, -1.0f, 7.0f })
            .set_scale(vec3 { 1.0f, 0.5f, 1.0f }),
        RigidBody { boxCollider, 0 },
        GltfScene {
            "assets/Models/BACKGROUND.glb",
            GltfFormat::BINARY,
        },
        Parent { mapEntity });

    // Generate ground
    auto groundEntity = wld.create_entity(
        Transform {}
            .set_translation(vec3 { 7.0f, 0.0f, 7.0f })
            .set_scale(vec3 { width / 2.0f, 2.0f, height / 2.0f }),
        RigidBody { boxColliderGround, 0 }, Parent { mapEntity });

    wld.create_entity(
        Transform {}
            .set_translation(vec3 { 0.0f, 0.075f, 0.0f })
            .set_scale(vec3 { 1.0f, 1.0f, 1.0f }),
        GltfScene {
            "assets/Models/GROUND.glb",
            GltfFormat::BINARY,
        },
        Parent { groundEntity });

    // Generate wall
    for (float i = 0; i < width; i++) {
        for (float j = 0; j < height; j++) {
            // First or last line is filled
            if (i == 0 || i == width - 1) {
                if (j == 0 || j == height - 1) {
                    float rot = 0.0f;
                    if (i == 0 && j == 0) {
                        // corner up left
                        rot = 180.f;
                    } else if (i == 0 && j == height - 1) {
                        // corner up right
                        rot = 270.0f;

                    } else if (i == width - 1 && j == 0) {
                        // corner low left
                        rot = 90.0f;

                    } else if (i == width - 1 && j == height - 1) {
                        // corner low right
                        rot = 0.0f;
                    }

                    wld.create_entity(
                        Transform::from_pos(vec3(i, 1.0f, j))
                            .set_scale(0.5f)
                            .set_rotation(vec3 { 0.0f, rot, 0.0f }),
                        RigidBody { boxCollider, 0 },
                        GltfScene {
                            "assets/Models/WALL_CORNER.glb",
                            GltfFormat::BINARY,
                        },
                        Parent { mapEntity });
                } else {
                    wld.create_entity(
                        Transform::from_pos(vec3(i, 1.0f, j)).set_scale(0.5f),
                        RigidBody { boxCollider, 0 },
                        GltfScene {
                            "assets/Models/WALL.glb",
                            GltfFormat::BINARY,
                        },
                        Parent { mapEntity });
                }
                // others lines only wall on first and last block
            } else if (j == 0 || j == height - 1) {
                wld.create_entity(
                    Transform::from_pos(vec3(i, 1.0f, j)).set_scale(0.5f),
                    RigidBody { boxCollider, 0 },
                    GltfScene {
                        "assets/Models/WALL.glb",
                        GltfFormat::BINARY,
                    },
                    Parent { mapEntity });
            }
        }
    }
}

void Map::LoadMapContent(World& wld, const MapRessources& map)
{
    Collider boxCollider = { ColliderType::BOX };
    boxCollider.box.extents = { 2.0f, 2.0f, 2.0f };

    for (auto& component : map.schema) {
        std::cout << (int)component.type << std::endl;
        if (component.type == MapComponentType::BLOCK_MUD) {
            wld.create_entity(
                Transform::from_pos(
                    vec3(component.x + 1, 1.0f, component.y + 1))
                    .set_scale(0.5f),
                RigidBody { boxCollider, 0 },
                GltfScene {
                    "assets/Models/BLOCK_MUD.glb",
                    GltfFormat::BINARY,
                },
                BreakableBlockTag {}, Parent { map.map_id });
        } else if (component.type == MapComponentType::MYSTERY_BOX) {
            wld.create_entity(
                Transform::from_pos(
                    vec3(component.x + 1, 1.0f, component.y + 1))
                    .set_scale(0.5f),
                RigidBody { boxCollider, 0 },
                GltfScene {
                    "assets/Models/MYSTERY_BOX.glb",
                    GltfFormat::BINARY,
                },
                Parent { map.map_id });
        } else if (component.type == MapComponentType::BLOCK_STONE) {
            wld.create_entity(
                Transform::from_pos(
                    vec3(component.x + 1, 1.0f, component.y + 1))
                    .set_scale(0.5f),
                RigidBody { boxCollider, 0 },
                GltfScene {
                    "assets/Models/BLOCK_STONE.glb",
                    GltfFormat::BINARY,
                },
                Parent { map.map_id });
        }
    }
}

std::vector<MapComponent> Map::GenerateMapSchema(World& wld, unsigned int seed)
{
    float bockMudPercent = 70;
    float bockStonePercent = 15;
    float bonusBlockPercent = 5;

    std::vector<MapComponent> map;
    glm::vec2 pos = { 13.0f, 13.0f };

    srand(seed);

    for (int i = 0; i < pos.y; i++) {
        for (int j = 1; j < pos.x - 1; j++) {
            MapComponent component;
            component.x = j;
            component.y = i;
            if ((i == 1 && j == 1) || (i == 1 && j == pos.x - 2)
                || (i == pos.y - 2 && j == 1)
                || (i == pos.y - 2 && j == pos.x - 2))
                // Players spawns;
                continue;
            else if (
                (i == 1 && j == 2) || (i == 1 && j == pos.x - 3)
                || (i == pos.y - 2 && j == 2)
                || (i == pos.y - 2 && j == pos.x - 3)
                || (i == pos.y - 3 && j == pos.x - 2)
                || (i == pos.y - 3 && j == 1) || (i == 2 && j == 1)
                || (i == 2 && j == pos.x - 2)) {
                // Empty case ?
            } else {
                int result = rand() % 100;
                if (result < bockMudPercent) {
                    component.type = MapComponentType::BLOCK_MUD;
                    map.push_back(component);
                } else if (result < bockMudPercent + bockStonePercent) {
                    component.type = MapComponentType::BLOCK_STONE;
                    map.push_back(component);
                } else if (
                    result
                    < bockMudPercent + bockStonePercent + bonusBlockPercent) {
                    component.type = MapComponentType::MYSTERY_BOX;
                    map.push_back(component);
                } else {
                    // Empty box ?;
                }
            }
        }
    }

    auto map_ressources = wld.get<MapRessources>();

    if (map_ressources) {
        map_ressources->schema = map;
    }

    return map;
}
