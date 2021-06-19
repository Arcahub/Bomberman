#include "scripts/MapGenerator.hpp"
#include "scripts/AIController.hpp"
#include "scripts/MysteryBox.hpp"
#include "scripts/PlayerController.hpp"
#include "scripts/SoloController.hpp"
#include "utils/Tag.hpp"

#include <fstream>
#include <iostream>
#include <string>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

using glm::vec2;
using glm::vec3;
using ige::asset::Material;
using ige::asset::Mesh;
using ige::asset::Texture;
using ige::plugin::animation::Animator;
using ige::plugin::gltf::GltfFormat;
using ige::plugin::gltf::GltfScene;
using ige::plugin::render::ImageRenderer;
using ige::plugin::render::MeshRenderer;
using ige::plugin::render::RectRenderer;
using ige::plugin::render::RenderPlugin;
using ige::plugin::render::Visibility;
using ige::plugin::transform::Parent;
using ige::plugin::transform::RectTransform;
using ige::plugin::transform::Transform;

using ige::plugin::physics::Collider;
using ige::plugin::physics::ColliderType;
using ige::plugin::physics::Constraint;
using ige::plugin::physics::GhostObject;
using ige::plugin::physics::PhysicsWorld;
using ige::plugin::physics::RigidBody;

using ige::plugin::ui::EventTarget;
using ige::plugin::ui::event::MouseClick;
using ige::plugin::ui::event::MouseEnter;
using ige::plugin::ui::event::MouseLeave;

void MapGenerator::on_start()
{
    SetUi();
}

void MapGenerator::tick()
{
    size_t current_player_number = 0;

    for (auto [ent, block, playerController, posPlayer] :
         world().query<PlayerTag, Scripts, Transform>()) {
        current_player_number++;
        int nbrlife = playerController.get<PlayerController>()->m_life_ui;
        if (playerController.get<PlayerController>()->m_life != nbrlife) {
            playerController.get<PlayerController>()->m_life_ui
                = playerController.get<PlayerController>()->m_life;
            nbrlife = playerController.get<PlayerController>()->m_life_ui;
            auto emptyHeartImg
                = Texture::make_new("assets/textures/heart_empty.png");
            auto fullHeartImg
                = Texture::make_new("assets/textures/heart_full.png");

            if (nbrlife >= 3)
                world().get_component<ImageRenderer>(textNbrPlayer[3])->texture
                    = fullHeartImg;
            else
                world().get_component<ImageRenderer>(textNbrPlayer[3])->texture
                    = emptyHeartImg;
            if (nbrlife >= 2)
                world().get_component<ImageRenderer>(textNbrPlayer[2])->texture
                    = fullHeartImg;
            else
                world().get_component<ImageRenderer>(textNbrPlayer[2])->texture
                    = emptyHeartImg;
            if (nbrlife >= 1)
                world().get_component<ImageRenderer>(textNbrPlayer[1])->texture
                    = fullHeartImg;
            else
                world().get_component<ImageRenderer>(textNbrPlayer[1])->texture
                    = emptyHeartImg;
        }
    }
    if (current_player_number != numberPlayer) {
        auto nbrImg = Texture::make_new(
            "assets/textures/Numbers/gradiant yellow/"
            + std::to_string(current_player_number) + ".png");

        numberPlayer = current_player_number;
        world().get_component<ImageRenderer>(textNbrPlayer[0])->texture
            = nbrImg;
        // std::cout << "####" << std::endl;
    }
}

void MapGenerator::SetUi()
{
    auto btnImg = Texture::make_new("assets/textures/head.png");
    auto nbrImg = Texture::make_new(
        "assets/textures/Numbers/gradiant yellow/"
        + std::to_string(numberPlayer) + ".png");
    auto fullHeartImg = Texture::make_new("assets/textures/heart_full.png");

    world().create_entity(
        RectTransform {}
            .set_anchors({ 1.0f, 0.0f }, { 1.0f, 0.0f })
            .set_bounds({ -75.0f, 0.0f }, { 0.0f, 75.0f }),
        ImageRenderer { btnImg, ImageRenderer::Mode::STRETCHED });

    textNbrPlayer.push_back(world().create_entity(
        RectTransform {}
            .set_anchors({ 1.0f, 0.0f }, { 1.0f, 0.0f })
            .set_bounds({ -112.5f, 10.0f }, { -62.5f, 60.0f }),
        ImageRenderer { nbrImg, ImageRenderer::Mode::STRETCHED }));

    textNbrPlayer.push_back(world().create_entity(
        RectTransform {}
            .set_anchors({ 0.0f, 1.0f }, { 0.0f, 1.0f })
            .set_bounds({ 0.0f, -75.0f }, { 75.0f, 0.0f }),
        ImageRenderer { fullHeartImg, ImageRenderer::Mode::STRETCHED }));

    textNbrPlayer.push_back(world().create_entity(
        RectTransform {}
            .set_anchors({ 0.0f, 1.0f }, { 0.0f, 1.0f })
            .set_bounds({ 75.0f, -75.0f }, { 150.0f, 0.0f }),
        ImageRenderer { fullHeartImg, ImageRenderer::Mode::STRETCHED }));

    textNbrPlayer.push_back(world().create_entity(
        RectTransform {}
            .set_anchors({ 0.0f, 1.0f }, { 0.0f, 1.0f })
            .set_bounds({ 150.0f, -75.0f }, { 225.0f, 0.0f }),
        ImageRenderer { fullHeartImg, ImageRenderer::Mode::STRETCHED }));
}
