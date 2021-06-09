#ifndef F31C6C2A_8C5E_4B01_92A8_E1A3FAA6121A
#define F31C6C2A_8C5E_4B01_92A8_E1A3FAA6121A

#include "NetworkId.hpp"
#include "Packet.hpp"
#include "Server.hpp"
#include "SynchroThreadBuffer.hpp"
#include "inl.hpp"
#include <concepts>
#include <deque>
#include <memory>
#include <string>
#include <thread>
#include <unordered_map>
#include <variant>

struct PlayerJoinEvent {
    NetworkId player_id;
};

struct PlayerLeaveEvent {
    NetworkId player_id;
};

using NetworkEvent = std::variant<PlayerJoinEvent, PlayerLeaveEvent>;

class NetworkManager {
public:
    Server* add_server(int port = -1);
    Server* server(const NetworkId& id);
    const Server* server(const NetworkId& id) const;
    bool remove_server(const NetworkId& id);

    void update();

private:
    std::unordered_map<NetworkId, std::shared_ptr<Server>> m_servers;
};

#endif /* F31C6C2A_8C5E_4B01_92A8_E1A3FAA6121A */
