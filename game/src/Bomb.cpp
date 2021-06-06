#include "Bomb.hpp"
#include "PlayerController.hpp"
#include "Tag.hpp"

#include <iostream>

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
        for (auto [ent, block, playerController] :
             world().query<Player, Scripts>()) {
            playerController.get<PlayerController>()->m_life--;
        }
        for (auto [ent, block, xformBlock] :
             world().query<BreakableBlock, Transform>()) {
            auto blockPos = xformBlock.world_translation();

            if (glm::distance(xform, blockPos) < 1.5f)
            /*(blockPos.x > (xform.x - 1) && blockPos.x < (xform.x + 1)
                && blockPos.y > (xform.y - 1) && blockPos.y < (xform.y + 1))*/
            {
                world().remove_entity(ent);
            }
        }
        world().remove_entity(this->entity());
        return;
    }
}