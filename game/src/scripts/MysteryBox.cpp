#include "scripts/MysteryBox.hpp"

using ige::ecs::World;
using ige::plugin::time::Time;
using ige::plugin::transform::Transform;

MysteryBox::MysteryBox()
{
}

MysteryBox::~MysteryBox()
{
}

void MysteryBox::update()
{
    auto time = world().get<Time>();
    auto xform = get_component<Transform>();

    xform->rotate(glm::vec3 { 25, 25, 25 } * time->delta_seconds());
}
