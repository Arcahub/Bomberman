//
// Created by mathias on 6/2/21.
//

#include "scripts/MapGenerator.hpp"
#include "Tag.hpp"
#include "scripts/AIController.hpp"
#include "scripts/PlayerController.hpp"
#include "scripts/SoloController.hpp"

#include <fstream>
#include <iostream>

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

void MapGenerator::on_start()
{
    std::ifstream file(GenerateCsv("assets/maps/MapTest.csv", true));
    std::vector<std::vector<std::string>> map = this->splitCsv(file);
    std::vector<std::vector<int>> mapMaze;
    std::vector<std::vector<int>> mapMazeEvent;
    auto playerResources = this->get_or_emplace_resource<PlayerResources>();
    Collider boxCollider = { ColliderType::BOX };
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
                auto blockEntity = this->world().create_entity(
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
                this->world().create_entity(
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
                this->world().create_entity(
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
                auto entityWall = this->world().create_entity(
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
                this->world().create_entity(
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
                this->world().create_entity(
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
                this->world().create_entity(
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
                this->world().create_entity(
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
                this->m_spawnPoints.push_back({ i, j });
            } else if (map[i][j] == "A") {
                maze.push_back(1);
                mazeEvent.push_back(0);
                this->world().create_entity(
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

    auto groundEntity = this->world().create_entity(
        Transform {}
            .set_translation(vec3 { 0.0f, 0.0f, 0.0f })
            .set_scale(vec3 { x * 0.5f, 2.0f, y * 0.5f }),
        RigidBody { boxColliderGround, 0 });

    this->world().create_entity(
        Transform {}
            .set_translation(vec3 { 0.0f, 0.075f, 0.0f })
            .set_scale(vec3 { 1.0f, 1.0f, 1.0f }),
        GltfScene {
            "assets/Models/GROUND.glb",
            GltfFormat::BINARY,
        },
        Parent { groundEntity });

    this->world().create_entity(
        Transform {}
            .set_translation(vec3 { 0.0f, -1.0f, 0.0f })
            .set_scale(vec3 { sizeMap * 0.01f, 0.5f, sizeMap * 0.01f }),
        RigidBody { boxCollider, 0 },
        GltfScene {
            "assets/Models/BACKGROUND.glb",
            GltfFormat::BINARY,
        });

    this->SpawnPlayer(mapMaze, mapMazeEvent);
}

void MapGenerator::tick()
{
    // std::cout << "!!" << std::endl;
}

void MapGenerator::SpawnPlayer(
    std::vector<std::vector<int>> mapMaze,
    std::vector<std::vector<int>> mapMazeEvent)
{
    int numberPlayer = 3;
    Collider boxCollider = { ColliderType::BOX };
    boxCollider.box.extents = { 0.25f, 0.25f, 0.25f };

    auto playerRoot = this->world().create_entity(
        Transform::from_pos(vec3(
            this->m_spawnPoints[0].x - (x / 2), 1.0f,
            this->m_spawnPoints[0].y - (y / 2))),
        RigidBody { boxCollider, 1, false }, Player {},
        Scripts::from(
            SoloController {}, PlayerController { blockMuds, posBlockMuds }));

    this->world().create_entity(
        Transform::from_pos(vec3(0.0f, -0.667f, 0.0f)).set_scale(0.25f),
        GltfScene {
            "assets/Bomberman_Play.glb",
            GltfFormat::BINARY,
        },
        Parent { playerRoot });

    for (int i = 0; i < numberPlayer; ++i) {
        auto playerRoot = this->world().create_entity(
            Transform::from_pos(vec3(
                this->m_spawnPoints[i + 1].x - (x / 2), 1.0f,
                this->m_spawnPoints[i + 1].y - (y / 2))),
            RigidBody { boxCollider, 1, false }, Enemy {},
            Scripts::from(
                AIController { blockMuds, posBlockMuds, mapMaze, mapMazeEvent },
                PlayerController { blockMuds, posBlockMuds }));

        this->world().create_entity(
            Transform::from_pos(vec3(0.0f, -0.667f, 0.0f)).set_scale(0.25f),
            GltfScene {
                "assets/Bomberman_Play.glb",
                GltfFormat::BINARY,
            },
            Parent { playerRoot });
    }
}

std::vector<std::vector<std::string>> MapGenerator::splitCsv(std::istream& str)
{
    std::vector<std::vector<std::string>> result;
    std::string line;

    while (std::getline(str, line)) {
        std::vector<std::string> resultLine;
        std::stringstream lineStream(line);
        std::string cell;

        while (std::getline(lineStream, cell, ',')) {
            resultLine.push_back(cell);
        }
        if (!lineStream && cell.empty())
            resultLine.push_back("");
        result.push_back(resultLine);
    }

    return result;
}

std::string MapGenerator::GenerateCsv(std::string csvName, bool newMap)
{
    glm::vec2 pos = { 13.0f, 13.0f };
    std::ofstream newCsv;

    if (newMap == false)
        return (csvName);
    newCsv.open("assets/maps/newMap.csv");
    for (int i = 0; i < pos.y; i++) {
        std::string line = "";
        if (i == 0) {
            line.push_back('4');
            for (int j = 1; j < pos.x - 1; j++) {
                line.push_back(',');
                line.push_back('3');
            }
            line.push_back(',');
            line.push_back('5');
        } else if (i == pos.y - 1) {
            line.push_back('6');
            for (int j = 1; j < pos.x - 1; j++) {
                line.push_back(',');
                line.push_back('3');
            }
            line.push_back(',');
            line.push_back('7');
        } else {
            line.push_back('3');
            for (int j = 1; j < pos.x - 1; j++) {
                line.push_back(',');
                if ((i == 1 && j == 1) || (i == 1 && j == pos.x - 2)
                    || (i == pos.y - 2 && j == 1)
                    || (i == pos.y - 2 && j == pos.x - 2))
                    line.push_back('2');
                else if (
                    (i == 1 && j == 2) || (i == 1 && j == pos.x - 3)
                    || (i == pos.y - 2 && j == 2)
                    || (i == pos.y - 2 && j == pos.x - 3)
                    || (i == pos.y - 3 && j == pos.x - 2)
                    || (i == pos.y - 3 && j == 1) || (i == 2 && j == 1)
                    || (i == 2 && j == pos.x - 2))
                    line.push_back('0');
                else if (nbrStair > 1 && i == x && j == y) {
                    nbrStair--;
                    line.push_back('8');
                } else {
                    int result = rand() % 100;
                    if (result < bockMudPercent)
                        line.push_back('1');
                    else if (result < bockMudPercent + bockStonePercent)
                        line.push_back('A');
                }
            }
            line.push_back(',');
            line.push_back('3');
        }
        line.push_back('\n');
        newCsv << line;
    }
    newCsv.close();
    return ("assets/maps/newMap.csv");
}