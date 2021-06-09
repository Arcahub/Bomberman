#ifndef A0B9D5BE_C26E_4C02_8171_E6D4CB4813D4
#define A0B9D5BE_C26E_4C02_8171_E6D4CB4813D4

#include <cstdint>
#include <optional>
#include <vector>

// struct PacketFormat {
//     uint8_t header = 0xBC;
//     uint32_t length;
//     std::vector<uint8_t> data;
// };

class Packet {
public:
    Packet();

    virtual ~Packet() = default;

    void set_data(const std::vector<char>& data);
    std::optional<std::vector<char>> get_data() const;

    virtual std::vector<char> serialize() const;
    virtual void serialize(std::vector<char>& buff) const;

    virtual bool deserialize(const std::vector<char>& data, size_t& bytes_read);

    virtual bool is_complete() const;
    virtual bool is_important() const;

protected:
    std::vector<char> m_data;

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

    uint32_t m_data_len;
    PacketState m_state;
};

#endif /* A0B9D5BE_C26E_4C02_8171_E6D4CB4813D4 */
