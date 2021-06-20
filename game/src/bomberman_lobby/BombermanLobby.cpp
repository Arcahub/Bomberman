#include <iostream>

#include "bomberman_lobby/BombermanLobby.hpp"
#include "bomberman_lobby/BombermanPacket.hpp"
#include "ige.hpp"
#include "scripts/AIController.hpp"
#include "scripts/NetworkController.hpp"
#include "scripts/SoloController.hpp"
#include "utils/Map.hpp"
#include "utils/Player.hpp"

using ige::ecs::EntityId;
using ige::ecs::World;
using ige::plugin::input::InputManager;
using ige::plugin::script::Scripts;
using ige::plugin::transform::Transform;

void BombermanLobby::start(int port)
{
    if (m_state != BombermanLobbyState::NOT_READY) {
        return;
    }
    m_room = std::make_unique<RoomServer>(port);
    m_state = BombermanLobbyState::LOBBY;
    m_side = Side::SERVER;
}

void BombermanLobby::join(const std::string& addr, int port)
{
    if (m_state != BombermanLobbyState::NOT_READY) {
        return;
    }
    m_room = std::make_unique<RoomClient>(addr, port);
    m_state = BombermanLobbyState::DISCONNECTED;
    m_side = Side::CLIENT;

    std::vector<char> data
        = { static_cast<char>(BombermanPacketType::PLAYER_JOIN) };

    m_room->send_room_data(data);
}

void BombermanLobby::add_player(const EntityId& entity_id)
{
    if (m_state == BombermanLobbyState::NOT_READY) {
        return;
    }
    if (m_side == Side::CLIENT) {
        if (m_state != BombermanLobbyState::LOBBY) {
            return;
        }
        std::vector<char> data
            = { static_cast<char>(BombermanPacketType::PLAYER_JOIN) };

        m_room->send_room_data(data);
    } else if (m_side == Side::SERVER) {
        if (m_state != BombermanLobbyState::LOBBY) {
            return;
        }
        auto player = m_room->add_player(RoomPlayerType::LOCAL, entity_id);

        auto room = dynamic_cast<RoomServer*>(m_room.get());

        auto players_packet = PlayerJoinPacket {}.serialize();

        for (auto pl : room->players()) {
            room->send_player_data(player, players_packet, *pl);
        }
    }
}

void BombermanLobby::spawn_players(World& wld, const MapRessources& map)
{
    int player_count = 0;

    if (m_state != BombermanLobbyState::GAME) {
        return;
    }
    for (const auto& player : map.player_spawns) {
        player_count++;
        auto pl = m_room->player(player.player_id);

        std::optional<EntityId> entity_id;
        if (pl) {
            wld.remove_entity(pl->entity_id);
            switch (pl->type) {
            case RoomPlayerType::LOCAL:
                entity_id = Player::spawn<SoloController>(wld, player.pos);
                break;
            case RoomPlayerType::NETWORK:
                entity_id = Player::spawn<NetworkController>(wld, player.pos);
                break;
            case RoomPlayerType::AI:
                entity_id = Player::spawn<AIController>(wld, player.pos);
                break;
            default:
                break;
            }
            pl->entity_id = *entity_id;
        }
    }

    for (; player_count < 4; player_count++) {
        auto entity_id
            = Player::spawn<AIController>(wld, MAP_SPAWNS[player_count]);

        m_room->add_player(RoomPlayerType::AI, entity_id);
    }
}

void BombermanLobby::leave()
{
    m_state = BombermanLobbyState::NOT_READY;
    if (m_side == Side::CLIENT) {
        for (auto& player : m_room->players()) {
            if (player->type == RoomPlayerType::LOCAL) {
                m_room->send_player_data(
                    *player, PlayerLeavePacket { player->id }.serialize());
            }
        }
        // close ?
    } else if (m_side == Side::SERVER) {
        m_room->send_room_data(RoomClosePacket {}.serialize());
        // close ?
    }
}

BombermanLobbyState BombermanLobby::state() const
{
    return m_state;
}

void BombermanLobby::set_settings(const BombermanLobbySettings& settings)
{
    m_settings = settings;
    m_room->send_room_data(LobbySettingsPacket { settings }.serialize());
}

BombermanLobbySettings BombermanLobby::get_settings() const
{
    return m_settings;
}

void BombermanLobby::start_game(World& wld)
{
    if (m_side == Side::CLIENT) {
        std::vector<char> data
            = { static_cast<char>(BombermanPacketType::PLAYER_STARTED_GAME) };
        m_room->send_room_data(data);
    } else if (m_side == Side::SERVER) {
        server_start_game(wld);
    }
}

void BombermanLobby::update(World& wld)
{
    try {
        if (m_state == BombermanLobbyState::NOT_READY) {
            return;
        }
        m_room->update();
        if (m_side == Side::CLIENT) {
            update_client(wld);
        } else if (m_side == Side::SERVER) {
            update_server(wld);
        }
    } catch (const std::exception& e) {
        std::cerr << "[Bomberman Lobby] " << e.what() << '\n';
        m_disconnected = true;
    }
}

void BombermanLobby::update_client(World& wld)
{
    while (auto data = m_room->recv()) {
        handle_packet_client(wld, *data);
        if (!m_room) {
            m_disconnected = true;
            return;
        }
    }

    auto manager = wld.get<InputManager<>>();

    if (manager) {
        for (auto player : m_room->players()) {
            if (player->type == RoomPlayerType::LOCAL) {
                // send local player input
                auto d = PlayerInputsPacket { *manager }.serialize();

                if (d.size() > 1) {
                    m_room->send_player_data(*player, d);
                }
            }
        }
    }
}

bool BombermanLobby::disconnected() const
{
    return m_disconnected;
}

void BombermanLobby::update_server(World& wld)
{
    while (auto packet = m_room->recv()) {
        handle_packet_server(wld, *packet);
    }

    auto manager = wld.get<InputManager<>>();

    if (manager) {
        for (auto player : m_room->players()) {

            if (player->type == RoomPlayerType::NETWORK
                && !((RoomServer*)m_room.get())->is_connected(*player)) {
                PlayerLeavePacket player_leave_packet
                    = PlayerLeavePacket { player->id };
                RoomPacket p;

                player_leave_packet.player_id = player->id;
                p.player_id = player->id;
                p.set_data(player_leave_packet.serialize());
                std::cout << "[Server] Player id: " << player->id
                          << " disconnected." << std::endl;
                handle_player_leave_packet(wld, p);
            }
            if (player->type == RoomPlayerType::LOCAL) {
                auto d = PlayerInputsPacket { *manager }.serialize();

                // send local player input
                if (d.size() > 1) {
                    m_room->send_player_data(*player, d);
                }
            }
        }
    }
}

void BombermanLobby::handle_packet_server(World& wld, RoomPacket& packet)
{
    if (packet.type == RoomPacketType::ROOM) {
        BombermanPacketType type
            = static_cast<BombermanPacketType>((packet.get_data())[0]);

        switch (type) {
        case BombermanPacketType::ROOM_SETTINGS_UPDATE:
            handle_room_settings_update_packet(wld, packet);
            break;
        case BombermanPacketType::ROOM_UPDATE:
            handle_room_update_packet(wld, packet);
            break;
        case BombermanPacketType::PLAYER_JOIN:
            handle_player_join_packet(wld, packet);
            break;
        case BombermanPacketType::PLAYER_STARTED_GAME:
            handle_player_started_game_packet(wld, packet);
            break;
        }
    } else if (packet.type == RoomPacketType::PLAYER) {
        BombermanPacketType type
            = static_cast<BombermanPacketType>((packet.get_data())[0]);

        switch (type) {
        case BombermanPacketType::PLAYER_INPUTS:
            handle_player_inputs_packet(wld, packet);
            break;
        default:
            break;
        }
    } else if (packet.type == RoomPacketType::DISCONNECT) {
        handle_player_leave_packet(wld, packet);
    }
}

void BombermanLobby::handle_packet_client(World& wld, RoomPacket& packet)
{
    BombermanPacketType type
        = static_cast<BombermanPacketType>((packet.get_data())[0]);

    if (packet.type == RoomPacketType::ROOM) {
        switch (type) {
        case BombermanPacketType::ROOM_JOIN:
            handle_room_join_packet(wld, packet);
            break;
        case BombermanPacketType::ROOM_SETTINGS_UPDATE:
            handle_room_settings_update_packet(wld, packet);
            break;
        case BombermanPacketType::ROOM_UPDATE:
            handle_room_update_packet(wld, packet);
            break;
        case BombermanPacketType::ROOM_CLOSE:
            handle_room_close_packet(wld, packet);
            break;
        case BombermanPacketType::GAME_START:
            handle_game_start_packet(wld, packet);
            break;
        }
    } else if (packet.type == RoomPacketType::PLAYER) {
        switch (type) {
        case BombermanPacketType::PLAYER_INPUTS:
            handle_player_inputs_packet(wld, packet);
            break;
        case BombermanPacketType::PLAYER_JOIN:
            handle_player_join_packet(wld, packet);
            break;
        case BombermanPacketType::PLAYER_LEAVE:
            handle_player_leave_packet(wld, packet);
            break;
        default:
            break;
        }
    }
}

void BombermanLobby::handle_room_join_packet(
    World& wld, const RoomPacket& packet)
{
    if (m_state != BombermanLobbyState::DISCONNECTED) {
        return;
    }

    if (m_side == Side::SERVER) {
        return;
    }

    RoomJoinPacket data = RoomJoinPacket::deserialize(packet.get_data());

    // Create players
    for (const auto& player : data.players) {
        auto entity_id = Player::spawn<NetworkController>(wld, player.position);
        m_room->add_player(RoomPlayerType::NETWORK, player.id, entity_id);
    }

    // Create self entity
    auto entity_id
        = Player::spawn<SoloController>(wld, glm::vec3 { 7.0f, 2.0f, 7.0f });
    m_room->add_player(RoomPlayerType::LOCAL, data.player_id, entity_id);

    m_state = BombermanLobbyState::LOBBY;
}

void BombermanLobby::handle_room_update_packet(
    World& wld, const RoomPacket& packet)
{
    if (m_state == BombermanLobbyState::DISCONNECTED) {
        return;
    }

    auto data = packet.get_data();

    // Update room (Currently no data)

    // if server broadcast to players
    if (m_side == Side::SERVER) {
        m_room->send_room_data(data);
    }
}

void BombermanLobby::handle_room_settings_update_packet(
    World& wld, const RoomPacket& packet)
{
    if (m_state != BombermanLobbyState::LOBBY) {
        return;
    }

    auto data = packet.get_data();

    m_settings = LobbySettingsPacket::deserialize(data).settings;

    // if server broadcast to players
    if (m_side == Side::SERVER) {
        m_room->send_room_data(data);
    }
}

void BombermanLobby::handle_room_close_packet(
    World& wld, const RoomPacket& packet)
{
    if (m_state == BombermanLobbyState::DISCONNECTED) {
        return;
    }

    if (m_side == Side::SERVER) {
        return;
    }

    // Client must return to menu

    m_room = nullptr;
    m_state = BombermanLobbyState::NOT_READY;
}

void BombermanLobby::handle_player_started_game_packet(
    World& wld, const RoomPacket& packet)
{
    if (m_state != BombermanLobbyState::LOBBY) {
        return;
    }

    if (m_side == Side::CLIENT) {
        return;
    }

    m_state = BombermanLobbyState::GAME;

    server_start_game(wld);
}

void BombermanLobby::handle_game_start_packet(
    World& wld, const RoomPacket& packet)
{
    if (m_state != BombermanLobbyState::LOBBY) {
        return;
    }
    std::cout << "RECV START GAME PACKET" << std::endl;

    if (m_side == Side::SERVER) {
        return;
    }

    GameStartPacket p = GameStartPacket::deserialize(packet.get_data());

    auto map_ressources = wld.get<MapRessources>();

    if (!map_ressources) {
        return;
    }
    m_state = BombermanLobbyState::GAME;
    map_ressources->schema = p.map_infos.map;
    map_ressources->player_spawns = p.players_spawn;
}

void BombermanLobby::handle_player_join_packet(
    World& wld, const RoomPacket& packet)
{
    if (m_state != BombermanLobbyState::LOBBY) {
        return;
    }

    if (m_side == Side::SERVER) {
        if (m_room->players().size() == 4) {
            return;
        }

        auto entity_id = Player::spawn<NetworkController>(
            wld, glm::vec3 { 7.0f, 2.0f, 7.0f });
        auto player = m_room->add_player(RoomPlayerType::NETWORK, entity_id);

        auto room = dynamic_cast<RoomServer*>(m_room.get());

        std::vector<RoomJoinPacket::Player> players;

        for (auto pl : room->players()) {
            if (pl->id == player.id) {
                continue;
            }
            auto transform = wld.get_component<Transform>(pl->entity_id);
            if (!transform) {
                continue;
            }
            players.push_back({ pl->id, transform->world_translation() });
        }

        RoomJoinPacket new_player_packet
            = RoomJoinPacket { player.id, players };
        room->send_room_data(new_player_packet.serialize(), packet.sender_id);

        auto players_packet = PlayerJoinPacket {}.serialize();

        for (auto pl : room->players()) {
            if (pl->id == player.id) {
                continue;
            }
            room->send_player_data(player, players_packet, *pl);
        }

    } else if (m_side == Side::CLIENT) {
        EntityId entity_id = Player::spawn<NetworkController>(
            wld, glm::vec3 { 7.0f, 2.0f, 7.0f });

        m_room->add_player(
            RoomPlayerType::NETWORK, *packet.player_id, entity_id);
    }
}

void BombermanLobby::handle_player_inputs_packet(
    World& wld, const RoomPacket& packet)
{
    if (m_state == BombermanLobbyState::DISCONNECTED) {
        return;
    }

    auto player = m_room->player(*packet.player_id);

    if (!player) {
        return;
    }

    auto scripts = wld.get_component<Scripts>(player->entity_id);

    if (!scripts) {
        return;
    }

    auto net_controller = scripts->get<NetworkController>();

    if (!net_controller) {
        return;
    }
    auto data = packet.get_data();
    auto input_packet = PlayerInputsPacket {}.deserialize(data);

    net_controller->actions = input_packet.actions;

    // if server broadcast to players
    if (m_side == Side::SERVER) {
        for (auto& pl : m_room->players()) {
            if (pl->id == packet.player_id) {
                continue;
            }
            auto room = dynamic_cast<RoomServer*>(m_room.get());
            room->send_player_data(*player, data, *pl);
        }
    }
}

void BombermanLobby::handle_player_leave_packet(
    World& wld, const RoomPacket& packet)
{
    if (m_state == BombermanLobbyState::DISCONNECTED) {
        return;
    }
    auto player = m_room->player(packet.player_id.value());

    if (!player || player->type != RoomPlayerType::NETWORK) {
        return;
    }

    // player->type = RoomPlayerType::AI;
    // auto scripts = wld.get_component<Scripts>(player->entity_id);
    // replace Network Controller to AIController;
    if (m_side == Side::SERVER) {
        for (auto& pl : m_room->players()) {
            if (pl->id == packet.player_id) {
                continue;
            }
            auto room = dynamic_cast<RoomServer*>(m_room.get());
            room->send_player_data(*player, packet.get_data(), *pl);
        }
    }

    // We remove the player for now
    wld.remove_entity(player->entity_id);
    m_room->remove_player(*player);
}

std::vector<RoomPlayer*> BombermanLobby::clients() const
{
    return m_room->players();
}

void BombermanLobby::server_start_game(World& wld)
{
    m_state = BombermanLobbyState::GAME;

    auto seed = time(NULL);
    auto map_schema = Map::GenerateMapSchema(wld, seed);
    std::vector<PlayerSpawn> players_spawn;
    size_t spawn_id = 0;

    for (auto& player : m_room->players()) {
        players_spawn.push_back({ player->id, MAP_SPAWNS[spawn_id] });
        spawn_id++;
    }

    auto map_ressources = wld.get<MapRessources>();
    map_ressources->player_spawns = players_spawn;

    GameStartPacket packet = { map_schema, players_spawn };
    m_room->send_room_data(packet.serialize());
}
