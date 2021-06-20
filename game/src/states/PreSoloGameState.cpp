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
    app.world().create_entity(Transform {}, Light::ambient(0.2));
    app.world().create_entity(Transform {}, Light::directional(0.8));

    auto& lobby = app.world().emplace<BombermanLobby>();

    lobby.start();
    Map::InitMap(app.world());

    lobby.add_player(Player::spawn(
        app.world(), SoloController {}, glm::vec3 { 7.0f, 2.0f, 7.0f }));
    lobby.start_game(app.world());
    app.state_machine().push<GameState>();
}

void PreSoloGameState::on_stop(App& app)
{
    auto map_ressource = app.world().get<MapRessources>();

    if (map_ressource) {
        app.world().remove_entity(map_ressource->map_id);
    }
}
