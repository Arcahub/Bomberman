#include "ige.hpp"
#include "plugin/BombermanLobbyPlugin.hpp"
#include "plugin/NetworkPlugin.hpp"
#include "plugin/RoomPlugin.hpp"
#include "states/RoomState.hpp"
#include "states/RootState.hpp"

#include <iostream>

using ige::core::App;
using ige::ecs::System;
// using ige::plugin::animation::AnimationPlugin;
using ige::plugin::audio::AudioPlugin;
using ige::plugin::gltf::GltfPlugin;
using ige::plugin::input::InputPlugin;
using ige::plugin::physics::PhysicsPlugin;
using ige::plugin::render::RenderPlugin;
using ige::plugin::script::ScriptPlugin;
using ige::plugin::time::Time;
using ige::plugin::time::TimePlugin;
using ige::plugin::transform::Transform;
using ige::plugin::transform::TransformPlugin;
using ige::plugin::ui::UiPlugin;
using ige::plugin::window::WindowPlugin;
using ige::plugin::window::WindowSettings;

#if defined(__linux__) | defined(OPEN_CONSOLE)

int main(int argc, char** argv)
{
#elif _WIN32
#include <tchar.h>
#include <windows.h>

int CALLBACK WinMain(
    _In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
    int argc = 1;
#endif

    std::cout << "Starting application..." << std::endl;

    App::Builder()
        .insert(WindowSettings { "Bomberman", 800, 600 })
        .insert(IsServerMarker {})
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
        .add_plugin(UiPlugin {})
        .add_plugin(AudioPlugin {})
        //.add_plugin(AnimationPlugin {})
        .run<RootState>();

    std::cout << "Bye bye!" << std::endl;
}
