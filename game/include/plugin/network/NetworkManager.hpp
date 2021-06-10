#ifndef F31C6C2A_8C5E_4B01_92A8_E1A3FAA6121A
#define F31C6C2A_8C5E_4B01_92A8_E1A3FAA6121A

#include "NetworkId.hpp"
#include "Packet.hpp"
#include <deque>
#include <memory>
#include <string>
#include <unordered_map>

class IClient {
public:
    virtual ~IClient() = default;
    virtual NetworkId id() const = 0;

    virtual void send(Packet& packet) = 0;
    virtual bool recv(Packet& packet) = 0;
};

class IServer {
public:
    virtual ~IServer() = default;
    virtual NetworkId id() const = 0;

    virtual void start_listening() = 0;
    virtual void stop_listening() = 0;

    virtual std::vector<IClient*> clients() = 0;
    virtual IClient* client(const NetworkId& id) = 0;

    virtual void disconnect_client(const NetworkId& id) = 0;
    virtual void disconnect_clients() = 0;

    virtual void send(Packet& packet) = 0;
    virtual void send(Packet& packet, const NetworkId& id) = 0;
};

class NetworkManager {
public:
    std::shared_ptr<IServer> add_server(int port = -1);
    std::shared_ptr<IServer> server(const NetworkId& id);
    const std::shared_ptr<IServer> server(const NetworkId& id) const;
    bool remove_server(const NetworkId& id);

    std::shared_ptr<IClient> add_client(const std::string& addr, int port);
    std::shared_ptr<IClient> client(const NetworkId& id);
    const std::shared_ptr<IClient> client(const NetworkId& id) const;
    bool remove_client(const NetworkId& id);

    void update();

private:
    class Client : public IClient {
    public:
        Client(const NetworkId& id, const std::string& addr, int port);
        Client(const std::string& addr, int port);

        NetworkId id() const;

        void send(Packet& packet);

        bool recv(Packet& packet);

        void update();

    private:
        NetworkId m_id;
        std::deque<uint8_t> m_read_buffer;
        std::deque<uint8_t> m_write_buffer;
    };

    class Server : public IServer {
    public:
        Server(const NetworkId& id, int port = -1);
        Server(int port = -1);

        NetworkId id() const;

        void start_listening();
        void stop_listening();

        std::vector<IClient*> clients();
        IClient* client(const NetworkId& id);

        void disconnect_client(const NetworkId& id);
        void disconnect_clients();

        void send(Packet& packet);
        void send(Packet& packet, const NetworkId& id);

        void update();

    private:
        NetworkId m_id;
        std::unordered_map<NetworkId, Client> m_clients;
    };

    std::unordered_map<NetworkId, std::shared_ptr<Server>> m_servers;
    std::unordered_map<NetworkId, std::shared_ptr<Client>> m_clients;
};

#endif /* F31C6C2A_8C5E_4B01_92A8_E1A3FAA6121A */
