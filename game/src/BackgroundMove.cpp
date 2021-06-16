#include "BackgroundMove.hpp"

using ige::ecs::World;
using ige::plugin::time::Time;
using ige::plugin::transform::RectTransform;

BackgroundMove::BackgroundMove()
{
}

BackgroundMove::~BackgroundMove()
{
}

void BackgroundMove::update()
{
    auto time = world().get<Time>();
    auto image = get_component<RectTransform>();

    image->set_anchors(
        image->anchors_min + time->delta_seconds() * glm::vec2 { 0.1, -0.1 },
        image->anchors_max + time->delta_seconds() * glm::vec2 { 0.1, -0.1 });

    if (image->anchors_min.x >= -0.024) {
        image->set_anchors(glm::vec2 { -1, 0 }, glm::vec2 { -1, 0 });
    }
}
