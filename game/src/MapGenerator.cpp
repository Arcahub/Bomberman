//
// Created by mathias on 6/2/21.
//

#include "MapGenerator.hpp"

#include <fstream>
#include <iostream>

#include <glm/vec3.hpp>

using glm::vec3;
using ige::asset::Material;
using ige::asset::Mesh;
using ige::plugin::render::MeshRenderer;
using ige::plugin::transform::Transform;
using ige::plugin::gltf::GltfFormat;
using ige::plugin::gltf::GltfScene;

struct PlayerResources {
    PlayerResources()
    {
        cube_mesh = Mesh::make_cube(1.0f);
        ground_mat = Material::make_default();
    }

    std::shared_ptr<Mesh> cube_mesh;
    std::shared_ptr<Material> ground_mat;
};

MapGenerator::MapGenerator()
{
}

MapGenerator::~MapGenerator()
{
}

void MapGenerator::on_start()
{
    std::ifstream file("assets/maps/MapTest.csv");
    std::vector<std::vector<std::string>> map = this->splitCsv(file);
    auto playerResources = this->get_or_emplace_resource<PlayerResources>();
    float sizeMap = 0;
    float x = -1.0f;
    float y = -1.0f;

    for (int i = 0; i < map.size(); i++, x++) {
        y = -1.0f;
        for (int j = 0; j < map[i].size(); j++, y++)
            sizeMap++;
    }
    sizeMap = sizeMap / 2;
    for (int i = 0; i < map.size(); ++i) {
        for (int j = 0; j < map[i].size(); ++j) {
            if (map[i][j] == "1"){
                this->world().create_entity(
                    Transform::from_pos(vec3(i - (x / 2), 1.0f, j - (y / 2))).set_scale(0.5f),
                    GltfScene {
                        "assets/Bombereman_Block_Mud.glb",
                        GltfFormat::BINARY,
                    });
            }
            else if (map[i][j] == "3"){
                this->world().create_entity(
                    Transform::from_pos(vec3(i - (x / 2), 1.0f, j - (y / 2))).set_scale(0.5f),
                    GltfScene {
                        "assets/Bombereman_Block_Clean.glb",
                        GltfFormat::BINARY,
                    });
            }
            std::cout << map[i][j];
        }
        std::cout << std::endl;
    }
    this->world().create_entity(
        Transform {}
            .set_translation(vec3 {
                0.0f,
                0.0f,
                0.0f,
            })
            .set_scale(vec3 { sizeMap * 0.1f, 0.5f, sizeMap * 0.1f }),
        GltfScene {
            "assets/Bombereman_Block_Clean.glb",
            GltfFormat::BINARY,
        });
}

void MapGenerator::tick()
{
    // std::cout << "!!" << std::endl;
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