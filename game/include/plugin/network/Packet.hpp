#ifndef A0B9D5BE_C26E_4C02_8171_E6D4CB4813D4
#define A0B9D5BE_C26E_4C02_8171_E6D4CB4813D4

#include <cstdint>
#include <deque>
#include <optional>

// struct PacketFormat {
//     uint8_t header = 0xBC;
//     u_int32_t length;
//     std::vector<uint8_t> data;
// };

class Packet {
public:
    Packet();

    virtual ~Packet() = default;

    void set_data(const std::deque<uint8_t>& data);
    std::optional<std::deque<uint8_t>> get_data() const;

    virtual std::deque<uint8_t> serialize() const;
    virtual void serialize(std::deque<uint8_t>& buff) const;

    virtual bool
    deserialize(const std::deque<uint8_t>& data, size_t& bytes_read);

    virtual bool is_complete() const;

protected:
    std::deque<uint8_t> m_data;

private:
    enum class PacketState {
        EMPTY,
        HEADER_VALIDATED,
        SIZE_1,
        SIZE_2,
        SIZE_3,
        SIZE_4,
        COMPLETE,
    };

    u_int32_t m_data_len;
    PacketState m_state;
};

#endif /* A0B9D5BE_C26E_4C02_8171_E6D4CB4813D4 */
