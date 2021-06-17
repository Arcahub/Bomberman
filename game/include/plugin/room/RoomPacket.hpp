#ifndef D118AB35_5791_4510_A462_51CBD82A1200
#define D118AB35_5791_4510_A462_51CBD82A1200

#include "RoomPlayerId.hpp"
#include "plugin/network/NetworkId.hpp"
#include <cstdint>
#include <optional>
#include <vector>

enum class RoomPacketType {
    ROOM,
    PLAYER,
    DISCONNECT
};

class RoomPacket {
public:
    RoomPacketType type;
    // Set on player_data send / recv
    std::optional<RoomPlayerId> player_id;

    // Set only when data is recv by server
    NetworkId sender_id;

    std::vector<char> serialize();
    void serialize(std::vector<char>& buff);

    static RoomPacket deserialize(const std::vector<char>& data);

    void set_data(const std::vector<char>& data);
    std::vector<char> get_data() const;

    virtual bool is_complete() const;

private:
    enum class RoomPacketState {
        EMPTY,
        TYPE,
        PLAYER_ID1,
        PLAYER_ID2,
        PLAYER_ID3,
        DATA_LEN1,
        DATA_LEN2,
        DATA_LEN3,
        DATA_LEN4,
        DATA,
        COMPLETE
    };

    std::vector<char> m_data;

    size_t m_player_id;
    RoomPacketState m_state = RoomPacketState::EMPTY;
};

#endif /* D118AB35_5791_4510_A462_51CBD82A1200 */
