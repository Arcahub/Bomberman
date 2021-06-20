#include "scripts/Bomb.hpp"
#include "scripts/AIController.hpp"
#include "scripts/PlayerController.hpp"
#include "utils/Tag.hpp"

using ige::plugin::audio::AudioClip;
using ige::plugin::audio::AudioSource;
using ige::plugin::time::Time;
using ige::plugin::transform::Transform;

Bomb::Bomb(int range)
    : m_range(range)
{
}

void Bomb::on_start()
{
    m_explosion_clock = std::chrono::steady_clock::now();
}

void Bomb::tick()
{
    auto now = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = now - m_explosion_clock;
    if (elapsed_seconds.count() > m_explosion_timer) {
        auto xform = get_component<Transform>()->world_translation();

        for (auto [ent, block, playerController, posPlayer] :
             world().query<PlayerTag, Scripts, Transform>()) {
            auto pos = posPlayer.world_translation();

            // if (glm::distance(xform, pos) < 1.25f + m_range)
            if ((pos.x > (xform.x - 1.25f - m_range)
                 && pos.x < (xform.x + 1.25f + m_range)
                 && pos.z > (xform.z - 0.5f) && pos.z < (xform.z + 0.5f))
                || (pos.x > (xform.x - 0.5f) && pos.x < (xform.x + 0.5f)
                    && pos.z > (xform.z - 1.25f - m_range)
                    && pos.z < (xform.z + 1.25f + m_range)))
                playerController.get<PlayerController>()->m_life--;
        }

        for (auto [ent, block, xformBlock] :
             world().query<BreakableBlockTag, Transform>()) {
            auto blockPos = xformBlock.world_translation();

            if ((blockPos.x > (xform.x - 1.75f - m_range)
                 && blockPos.x < (xform.x + 1.75f + m_range)
                 && blockPos.z > (xform.z - 0.5f)
                 && blockPos.z < (xform.z + 0.5f))
                || (blockPos.x > (xform.x - 0.5f)
                    && blockPos.x < (xform.x + 0.5f)
                    && blockPos.z > (xform.z - 1.75f - m_range)
                    && blockPos.z < (xform.z + 1.75f + m_range))) {
                world().remove_entity(ent);
            }
        }
        std::optional<ige::ecs::EntityId> audioSource
            = world().create_entity(AudioSource {}, Transform {});
        auto audioSourceEnt
            = world().get_component<AudioSource>(audioSource.value());
        auto clip = AudioClip::load("./assets/sound/BoomSoundEffect.ogg");

        audioSourceEnt->load_clip(clip);
        audioSourceEnt->play();
        world().remove_entity(this->entity());
        return;
    }
}
