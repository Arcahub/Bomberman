#ifndef D118AB35_5791_4510_A462_51CBD82A1200
#define D118AB35_5791_4510_A462_51CBD82A1200

#include "plugin/network/NetworkId.hpp"
#include "plugin/network/Packet.hpp"
#include <optional>

enum class RoomPacketType {
    ROOM,
    PLAYER,
};

class RoomPacket : public Packet {
public:
    RoomPacketType type;
    std::optional<NetworkId> netword_id;

    virtual std::deque<uint8_t> serialize() override;
    virtual void serialize(std::deque<uint8_t>& buff) override;

    virtual bool
    deserialize(const std::deque<uint8_t>& data, size_t& bytes_read) override;

    virtual bool is_complete() const override;

private:
    enum class RoomPacketState {
        EMPTY,
        TYPE,
        PLAYER_ID1,
        PLAYER_ID2,
        PLAYER_ID3,
        COMPLETE
    };

    size_t m_network_id;
    RoomPacketState m_state;
};

#endif /* D118AB35_5791_4510_A462_51CBD82A1200 */
