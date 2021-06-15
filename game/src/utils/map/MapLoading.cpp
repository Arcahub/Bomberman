#include "utils/map/MapLoading.hpp"
#include "Tag.hpp"
#include "ige.hpp"
#include "scripts/AIController.hpp"
#include "scripts/PlayerController.hpp"
#include "scripts/SoloController.hpp"
#include "utils/CsvUtils.hpp"

#include <fstream>
#include <iostream>
#include <sstream>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

using glm::vec2;
using glm::vec3;
using ige::asset::Material;
using ige::asset::Mesh;
using ige::plugin::gltf::GltfFormat;
using ige::plugin::gltf::GltfScene;
using ige::plugin::render::MeshRenderer;
using ige::plugin::transform::Parent;
using ige::plugin::transform::Transform;

using ige::plugin::physics::Collider;
using ige::plugin::physics::ColliderType;
using ige::plugin::physics::Constraint;
using ige::plugin::physics::PhysicsWorld;
using ige::plugin::physics::RigidBody;

struct PlayerResources {
    PlayerResources()
    {
        cube_mesh = Mesh::make_cube(1.0f);
        ground_mat = Material::make_default();
    }

    std::shared_ptr<Mesh> cube_mesh;
    std::shared_ptr<Material> ground_mat;
};

void MapLoading::LoadMap(ige::core::App& app, const std::string& map_raw)
{
    std::vector<std::vector<std::string>> map = CsvUtils::SplitCsv(map_raw);
    std::vector<std::vector<int>> mapMaze;
    std::vector<std::vector<int>> mapMazeEvent;
    auto playerResources = app.world().get_or_emplace<PlayerResources>();
    Collider boxCollider = { ColliderType::BOX };
    std::vector<glm::ivec2> m_spawnPoints;
    std::vector<ige::ecs::EntityId> blockMuds;
    std::vector<glm::vec2> posBlockMuds;
    float sizeMap = 0;
    float x = -1.0f;
    float y = -1.0f;

    int nbrStair = 2;
    float bockMudPercent = 75;
    float bockStonePercent = 25;
    boxCollider.box.extents = { 2.0f, 2.0f, 2.0f };

    for (int i = 0; i < map.size(); i++, x++) {
        y = -1.0f;
        for (int j = 0; j < map[i].size(); j++, y++)
            sizeMap++;
    }
    sizeMap = sizeMap / 2;
    for (int i = 0; i < map.size(); ++i) {
        std::vector<int> maze;
        std::vector<int> mazeEvent;

        for (int j = 0; j < map[i].size(); ++j) {
            if (map[i][j] == "1") {
                maze.push_back(0);
                mazeEvent.push_back(2);
                glm::vec2 pos = { i - (x / 2), j - (y / 2) };
                posBlockMuds.push_back(pos);
                auto blockEntity = app.world().create_entity(
                    Transform::from_pos(vec3(i - (x / 2), 1.0f, j - (y / 2)))
                        .set_scale(0.5f),
                    RigidBody { boxCollider, 0 }, BreakableBlock {},
                    GltfScene {
                        "assets/Models/BLOCK_MUD.glb",
                        GltfFormat::BINARY,
                    });
                blockMuds.push_back(blockEntity);
            } else if (map[i][j] == "3") {
                maze.push_back(1);
                mazeEvent.push_back(0);
                app.world().create_entity(
                    Transform::from_pos(vec3(i - (x / 2), 1.0f, j - (y / 2)))
                        .set_scale(0.5f),
                    RigidBody { boxCollider, 0 },
                    GltfScene {
                        "assets/Models/WALL.glb",
                        GltfFormat::BINARY,
                    });
            } else if (map[i][j] == "4") {
                maze.push_back(1);
                mazeEvent.push_back(0);
                app.world().create_entity(
                    Transform::from_pos(vec3(i - (x / 2), 1.0f, j - (y / 2)))
                        .set_scale(0.5f)
                        .set_rotation(vec3 { 0.0f, 180.0f, 0.0f }),
                    RigidBody { boxCollider, 0 },
                    GltfScene {
                        "assets/Models/WALL_CORNER.glb",
                        GltfFormat::BINARY,
                    });
            } else if (map[i][j] == "5") {
                maze.push_back(1);
                mazeEvent.push_back(0);
                auto entityWall = app.world().create_entity(
                    Transform::from_pos(vec3(i - (x / 2), 1.0f, j - (y / 2)))
                        .set_scale(0.5f)
                        .set_rotation(vec3 { 0.0f, 270.0f, 0.0f }),
                    RigidBody { boxCollider, 0 },
                    GltfScene {
                        "assets/Models/WALL_CORNER.glb",
                        GltfFormat::BINARY,
                    });
            } else if (map[i][j] == "6") {
                maze.push_back(1);
                mazeEvent.push_back(0);
                app.world().create_entity(
                    Transform::from_pos(vec3(i - (x / 2), 1.0f, j - (y / 2)))
                        .set_scale(0.5f)
                        .set_rotation(vec3 { 0.0f, 90.0f, 0.0f }),
                    RigidBody { boxCollider, 0 },
                    GltfScene {
                        "assets/Models/WALL_CORNER.glb",
                        GltfFormat::BINARY,
                    });
            } else if (map[i][j] == "7") {
                maze.push_back(1);
                mazeEvent.push_back(0);
                app.world().create_entity(
                    Transform::from_pos(vec3(i - (x / 2), 1.0f, j - (y / 2)))
                        .set_scale(0.5f)
                        .set_rotation(vec3 { 0.0f, 0.0f, 0.0f }),
                    RigidBody { boxCollider, 0 },
                    GltfScene {
                        "assets/Models/WALL_CORNER.glb",
                        GltfFormat::BINARY,
                    });
            } else if (map[i][j] == "8") {
                maze.push_back(1);
                mazeEvent.push_back(0);
                app.world().create_entity(
                    Transform::from_pos(vec3(i - (x / 2), 1.0f, j - (y / 2)))
                        .set_scale(0.5f),
                    RigidBody { boxCollider, 0 },
                    GltfScene {
                        "assets/Models/STAIR.glb",
                        GltfFormat::BINARY,
                    });
            } else if (map[i][j] == "9") {
                maze.push_back(1);
                mazeEvent.push_back(0);
                app.world().create_entity(
                    Transform::from_pos(vec3(i - (x / 2), 1.0f, j - (y / 2)))
                        .set_scale(0.5f),
                    RigidBody { boxCollider, 0 },
                    GltfScene {
                        "assets/Models/MYSTERY_BOX.glb",
                        GltfFormat::BINARY,
                    });
            } else if (map[i][j] == "2") {
                maze.push_back(0);
                mazeEvent.push_back(0);
                // Spawn point
                // app.m_spawnPoints.push_back({ i, j });
            } else if (map[i][j] == "A") {
                maze.push_back(1);
                mazeEvent.push_back(0);
                app.world().create_entity(
                    Transform::from_pos(vec3(i - (x / 2), 1.0f, j - (y / 2)))
                        .set_scale(0.5f),
                    RigidBody { boxCollider, 0 },
                    GltfScene {
                        "assets/Models/BLOCK_STONE.glb",
                        GltfFormat::BINARY,
                    });
            } else {
                maze.push_back(0);
                mazeEvent.push_back(0);
            }
        }
        mapMaze.push_back(maze);
        mapMazeEvent.push_back(mazeEvent);
    }
    Collider boxColliderGround = { ColliderType::BOX };
    boxColliderGround.box.extents = { 2.0f, 0.5f, 2.0f };

    auto groundEntity = app.world().create_entity(
        Transform {}
            .set_translation(vec3 { 0.0f, 0.0f, 0.0f })
            .set_scale(vec3 { x * 0.5f, 2.0f, y * 0.5f }),
        RigidBody { boxColliderGround, 0 });

    app.world().create_entity(
        Transform {}
            .set_translation(vec3 { 0.0f, 0.075f, 0.0f })
            .set_scale(vec3 { 1.0f, 1.0f, 1.0f }),
        GltfScene {
            "assets/Models/GROUND.glb",
            GltfFormat::BINARY,
        },
        Parent { groundEntity });

    app.world().create_entity(
        Transform {}
            .set_translation(vec3 { 0.0f, -1.0f, 0.0f })
            .set_scale(vec3 { sizeMap * 0.01f, 0.5f, sizeMap * 0.01f }),
        RigidBody { boxCollider, 0 },
        GltfScene {
            "assets/Models/BACKGROUND.glb",
            GltfFormat::BINARY,
        });

    // SpawnPlayer(mapMaze, mapMazeEvent);
}
