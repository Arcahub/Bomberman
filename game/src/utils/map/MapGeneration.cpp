#include "utils/map/MapGeneration.hpp"
#include "Tag.hpp"
#include "ige.hpp"

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

std::string MapGeneration::GenerateRoomMap()
{
    glm::vec2 pos = { 13.0f, 13.0f };
    std::stringstream newCsv;

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
            }
            line.push_back(',');
            line.push_back('3');
        }
        line.push_back('\n');
        newCsv << line;
    }
    return newCsv.str();
}
