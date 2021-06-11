#ifndef D118AB35_5791_4510_A462_51CBD82A1200
#define D118AB35_5791_4510_A462_51CBD82A1200

#include "plugin/network/NetworkId.hpp"
#include <cstdint>
#include <optional>
#include <vector>

enum class RoomPacketType {
    ROOM,
    PLAYER,
};

class RoomPacket {
public:
    RoomPacketType type;
    std::optional<NetworkId> netword_id;

    virtual std::vector<char> serialize();
    virtual void serialize(std::vector<char>& buff);

    virtual bool deserialize(const std::vector<char>& data);

    void set_data(const std::vector<char>& data);
    std::optional<std::vector<char>> get_data() const;

    virtual bool is_complete() const;

private:
    enum class RoomPacketState {
        EMPTY,
        TYPE,
        PLAYER_ID1,
        PLAYER_ID2,
        PLAYER_ID3,
        COMPLETE
    };

    std::vector<char> m_data;

    size_t m_network_id;
    RoomPacketState m_state;
};

#endif /* D118AB35_5791_4510_A462_51CBD82A1200 */
