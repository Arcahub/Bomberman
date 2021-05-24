#include "RootState.hpp"
#include "ige.hpp"
#include <iostream>

using ige::core::App;
using ige::plugin::gltf::GltfPlugin;
using ige::plugin::input::InputPlugin;
using ige::plugin::render::RenderPlugin;
using ige::plugin::transform::TransformPlugin;
using ige::plugin::window::WindowPlugin;
using ige::plugin::window::WindowSettings;

int main()
{
    std::cout << "Starting application..." << std::endl;

    App::Builder()
        .insert(WindowSettings { "Hello, World!", 800, 600 })
        .add_plugin(TransformPlugin {})
        .add_plugin(WindowPlugin {})
        .add_plugin(RenderPlugin {})
        .add_plugin(InputPlugin {})
        .add_plugin(GltfPlugin {})
        .run<RootState>();

    std::cout << "Bye bye!" << std::endl;
}
