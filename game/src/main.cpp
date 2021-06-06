#include "RootState.hpp"
#include "ige.hpp"
#include "plugin/NetworkPlugin.hpp"
#include "plugin/RoomPlugin.hpp"
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

int main()
{
    std::cout << "Starting application..." << std::endl;

    App::Builder()
        .insert(WindowSettings { "Hello, World!", 800, 600 })
        .add_plugin(InputPlugin {})
        .add_plugin(TimePlugin {})
        .add_plugin(TransformPlugin {})
        .add_plugin(WindowPlugin {})
        .add_plugin(RenderPlugin {})
        .add_plugin(ScriptPlugin {})
        .add_plugin(PhysicsPlugin {})
        .add_plugin(NetworkPlugin {})
        .add_plugin(RoomPlugin {})
        .run<RootState>();

    std::cout << "Bye bye!" << std::endl;
}
