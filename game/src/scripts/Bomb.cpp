#include "scripts/Bomb.hpp"
#include "scripts/AIController.hpp"
#include "scripts/PlayerController.hpp"
#include "utils/Tag.hpp"

using ige::plugin::audio::AudioClip;
using ige::plugin::audio::AudioSource;
using ige::plugin::time::Time;
using ige::plugin::transform::Transform;

Bomb::Bomb(
    std::vector<ige::ecs::EntityId> blockMuds,
    std::vector<glm::vec2> posBlockMuds)
{
    m_blockMuds = blockMuds;
    m_posBlockMuds = posBlockMuds;
    explosed = 5.0f;
}

Bomb::~Bomb()
{
}

void Bomb::on_start()
{
}

void Bomb::update()
{
    if (explosed > 0)
        explosed -= get_resource<Time>()->delta_seconds();
    else if (isDone == false) {
        auto xform = get_component<Transform>()->translation();

        isDone = true;
        for (auto [ent, block, playerController, posPlayer] :
             world().query<Player, Scripts, Transform>()) {
            auto pos = posPlayer.world_translation();

            if (glm::distance(xform, pos) < 1.25f)
                playerController.get<PlayerController>()->m_life--;
        }
        for (auto [ent, block, aiController, posAI] :
             world().query<Enemy, Scripts, Transform>()) {
            auto pos = posAI.world_translation();

            if (glm::distance(xform, pos) < 1.25f)
                aiController.get<AIController>()->m_life--;
        }
        for (auto [ent, block, xformBlock] :
             world().query<BreakableBlock, Transform>()) {
            auto blockPos = xformBlock.world_translation();

            if ((blockPos.x > (xform.x - 1.75f)
                 && blockPos.x < (xform.x + 1.75f)
                 && blockPos.z > (xform.z - 0.5f)
                 && blockPos.z < (xform.z + 0.5f))
                || (blockPos.x > (xform.x - 0.5f)
                    && blockPos.x < (xform.x + 0.5f)
                    && blockPos.z > (xform.z - 1.75f)
                    && blockPos.z < (xform.z + 1.75f))) {
                world().remove_entity(ent);
            }
        }
        std::optional<ige::ecs::EntityId> audioSource
            = world().create_entity(AudioSource {}, Transform {});
        auto audioSourceEnt
            = world().get_component<AudioSource>(audioSource.value());
        std::shared_ptr<AudioClip> clip(
            new AudioClip("./assets/sound/BoomSoundEffect.ogg"));

        audioSourceEnt->load_clip(clip);
        audioSourceEnt->play();
        world().remove_entity(this->entity());
        return;
    }
}
