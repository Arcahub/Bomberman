#include "states/PreSoloGameState.hpp"
#include "bomberman_lobby/BombermanLobby.hpp"
#include "scripts/SoloController.hpp"
#include "states/GameState.hpp"
#include "utils/Map.hpp"
#include "utils/Player.hpp"

using ige::core::App;
using ige::plugin::render::Light;
using ige::plugin::transform::Transform;

void PreSoloGameState::on_start(App& app)
{
    auto& lobby = app.world().emplace<BombermanLobby>();

    lobby.start();
    Map::InitMap(app.world());

    lobby.add_player(Player::spawn(
        app.world(), SoloController {}, glm::vec3 { 7.0f, 2.0f, 7.0f }));
    lobby.start_game(app.world());
    app.state_machine().switch_to<GameState::Loader>();
}

void PreSoloGameState::on_stop(App& app)
{
}
