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
    ~Packet() = default;

    void set_data(const std::vector<char>& data);
    std::optional<std::vector<char>> get_data() const;

    void is_important(bool is_important);
    bool is_important() const;

protected:
    std::vector<char> m_data;

private:
    bool m_important;
};

#endif /* A0B9D5BE_C26E_4C02_8171_E6D4CB4813D4 */
