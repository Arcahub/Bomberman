#include "Bomb.hpp"

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
    else {
        auto xform = get_component<Transform>()->translation();

        for (int i = 0; i < m_blockMuds.size(); ++i) {
            // std::cout << xform.x << " / " << m_posBlockMuds[i].x << " // "
            //           << xform.y << " / " << m_posBlockMuds[i].y <<
            //           std::endl;
            if (m_posBlockMuds[i].x > (xform.x - 1)
                && m_posBlockMuds[i].x < (xform.x + 1)
                && m_posBlockMuds[i].y > (xform.y - 1)
                && m_posBlockMuds[i].y < (xform.y + 1)) {
                world().remove_entity(m_blockMuds[i]);
                m_blockMuds.erase(m_blockMuds.begin() + i);
                m_posBlockMuds.erase(m_posBlockMuds.begin() + i);
            }
        }
        world().remove_entity(this->entity());
        return;
    }
}