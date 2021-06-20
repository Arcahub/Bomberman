#include "scripts/MysteryBox.hpp"
#include "scripts/PlayerController.hpp"
#include "scripts/TrackballCamera.hpp"
#include "utils/Tag.hpp"

#include <random>

using ige::ecs::World;
using ige::plugin::audio::AudioClip;
using ige::plugin::audio::AudioSource;
using ige::plugin::physics::PhysicsWorld;
using ige::plugin::time::Time;
using ige::plugin::transform::Transform;

MysteryBox::MysteryBox()
{
}

MysteryBox::~MysteryBox()
{
}

void MysteryBox::on_start()
{
    audioSource = world().create_entity(AudioSource {}, Transform {});
    m_audioSource = world().get_component<AudioSource>(audioSource.value());
}

void MysteryBox::update()
{
    auto time = world().get<Time>();
    auto xform = get_component<Transform>();
    auto physics_world = world().get<PhysicsWorld>();

    xform->rotate(glm::vec3 { 25, 25, 25 } * time->delta_seconds());

    if (physics_world) {
        for (auto [entPlayer, block, playerController, posPlayer] :
             world().query<PlayerTag, Scripts, Transform>()) {
            if (physics_world->collide(entPlayer, entity())) {
                ApplyEffect(playerController);
            }
        }
    }
}

void MysteryBox::ApplyEffect(ige::plugin::script::Scripts& playerController)
{
    int result = rand() % 5;
    auto playerControllerScp = playerController.get<PlayerController>();

    switch (result) {
    case 0:
        // good sound
        PlayAudio(0);
        playerControllerScp->m_speed += 1.0f;
        break;
    case 1:
        // maluss sound
        PlayAudio(1);
        playerControllerScp->m_reverseControlle = true;
        break;
    case 2:
        // maluss sound
        PlayAudio(1);
        for (auto [ent, block, camController] :
             world().query<CamTag, Scripts>()) {
            auto cam = camController.get<TrackballCamera>();

            cam->m_distance = 15.0f;
            cam->m_theta = -3.1446f;
            cam->m_phi = 0.208098f;
            cam->update_transform();
            playerControllerScp->cam = cam;
            playerControllerScp->reverseCamCount = 20.0f;
            playerControllerScp->m_reverseCam = false;
        }
        break;
    case 3:
        // good sound
        PlayAudio(0);
        playerControllerScp->m_rangeBomb += 1;
        break;
    default:
        // good sound
        PlayAudio(0);
        playerControllerScp->m_actionSpeed -= 1.0f;
        break;
    }

    world().remove_entity(entity());
}

void MysteryBox::PlayAudio(int idSound)
{
    if (idSound == 0) {
        std::shared_ptr<AudioClip> clip(
            new AudioClip("./assets/sound/BonusSoundEffect.ogg"));

        m_audioSource->load_clip(clip);
        m_audioSource->play();
    } else {
        std::shared_ptr<AudioClip> clip(
            new AudioClip("./assets/sound/NegativeSoundEffect.ogg"));

        m_audioSource->load_clip(clip);
        m_audioSource->play();
    }
}