#ifndef B89774D8_E1BA_456B_912E_BDB7927ECD2F
#define B89774D8_E1BA_456B_912E_BDB7927ECD2F

#include "BombermanLobbySettings.hpp"
#include "BombermanPacket.hpp"
#include "ige.hpp"
#include "plugin/room/RoomClient.hpp"
#include "plugin/room/RoomServer.hpp"
#include <string>
#include <variant>

enum class BombermanLobbyState {
    NOT_READY,
    DISCONNECTED,
    LOBBY,
    GAME,
};

class BombermanLobby {
public:
    void start(int port = -1);
    void join(const std::string& addr, int port);
    void leave();

    void add_player();

    void set_settings(const BombermanLobbySettings& settings);
    BombermanLobbySettings get_settings() const;

    void start_game(ige::ecs::World& wld);

    BombermanLobbyState state() const;
    std::vector<RoomPlayer*> clients() const;
    void update(ige::ecs::World& wld);

private:
    void update_client(ige::ecs::World& wld);
    void update_server(ige::ecs::World& wld);

    void handle_packet_server(ige::ecs::World& wld, RoomPacket& packet);
    void handle_packet_client(ige::ecs::World& wld, RoomPacket& packet);

    void
    handle_room_join_packet(ige::ecs::World& wld, const RoomPacket& packet);
    void handle_room_settings_update_packet(
        ige::ecs::World& wld, const RoomPacket& packet);
    void
    handle_room_update_packet(ige::ecs::World& wld, const RoomPacket& packet);
    void
    handle_room_close_packet(ige::ecs::World& wld, const RoomPacket& packet);
    void handle_player_started_game_packet(
        ige::ecs::World& wld, const RoomPacket& packet);
    void
    handle_game_start_packet(ige::ecs::World& wld, const RoomPacket& packet);
    void
    handle_player_join_packet(ige::ecs::World& wld, const RoomPacket& packet);
    void
    handle_player_inputs_packet(ige::ecs::World& wld, const RoomPacket& packet);
    void
    handle_player_leave_packet(ige::ecs::World& wld, const RoomPacket& packet);

    void server_start_game(ige::ecs::World& wld);

    enum class Side { CLIENT, SERVER };

    Side m_side;
    std::unique_ptr<Room> m_room;

    BombermanLobbySettings m_settings;
    BombermanLobbyState m_state = BombermanLobbyState::NOT_READY;
};

#endif /* B89774D8_E1BA_456B_912E_BDB7927ECD2F */
