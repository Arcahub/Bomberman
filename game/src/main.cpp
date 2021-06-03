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

#ifdef __linux__

int main()

#elif _WIN32
#include <tchar.h>
#include <windows.h>

int CALLBACK WinMain(
    _In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine, _In_ int nCmdShow)

#endif

{
    std::cout << "Starting application..." << std::endl;

    App::Builder()
        .insert(WindowSettings { "Bomberman", 800, 600 })
        .add_plugin(InputPlugin {})
        .add_plugin(TimePlugin {})
        .add_plugin(TransformPlugin {})
        .add_plugin(PhysicsPlugin {})
        .add_plugin(WindowPlugin {})
        .add_plugin(RenderPlugin {})
        .add_plugin(GltfPlugin {})
        .add_plugin(ScriptPlugin {})
        .add_plugin(NetworkPlugin {})
        .add_plugin(RoomPlugin {})
        .run<RootState>();

    std::cout << "Bye bye!" << std::endl;
}
