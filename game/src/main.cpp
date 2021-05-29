#include "RootState.hpp"
#include "ige.hpp"
#include <iostream>

using ige::core::App;
using ige::plugin::gltf::GltfPlugin;
using ige::plugin::input::InputPlugin;
using ige::plugin::physics::PhysicsPlugin;
using ige::plugin::render::RenderPlugin;
using ige::plugin::script::ScriptPlugin;
using ige::plugin::time::TimePlugin;
using ige::plugin::transform::TransformPlugin;
using ige::plugin::window::WindowPlugin;
using ige::plugin::window::WindowSettings;
using ige::plugin::script::ScriptPlugin;
using ige::plugin::time::TimePlugin;

int main()
{
    std::cout << "Starting application..." << std::endl;

    App::Builder()
        .insert(WindowSettings { "Bomberman", 800, 600 })
        .add_plugin(TimePlugin {})
        .add_plugin(TransformPlugin {})
        .add_plugin(WindowPlugin {})
        .add_plugin(RenderPlugin {})
        .add_plugin(InputPlugin {})
        .add_plugin(GltfPlugin {})
        .add_plugin(ScriptPlugin {})
        .run<RootState>();

    std::cout << "Bye bye!" << std::endl;
}
