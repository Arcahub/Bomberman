#ifndef F31C6C2A_8C5E_4B01_92A8_E1A3FAA6121A
#define F31C6C2A_8C5E_4B01_92A8_E1A3FAA6121A

#include "NetworkId.hpp"
#include "Server.hpp"
#include <memory>
#include <unordered_map>

class NetworkManager {
public:
    std::shared_ptr<Server> add_server(int port = -1);
    std::shared_ptr<Server> server(const NetworkId& id);
    const std::shared_ptr<Server> server(const NetworkId& id) const;
    bool remove_server(const NetworkId& id);

    void update();

private:
    std::unordered_map<NetworkId, std::shared_ptr<Server>> m_servers;
};

#endif /* F31C6C2A_8C5E_4B01_92A8_E1A3FAA6121A */
