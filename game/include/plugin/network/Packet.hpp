#ifndef A0B9D5BE_C26E_4C02_8171_E6D4CB4813D4
#define A0B9D5BE_C26E_4C02_8171_E6D4CB4813D4

#include <cstdint>
#include <optional>
#include <vector>

class Packet {
public:
    Packet();

    void set_data(const std::vector<char>& data);
    std::vector<char> get_data() const;

    void is_important(bool is_important);
    bool is_important() const;

protected:
    std::vector<char> m_data;

private:
    bool m_important;
};

#endif /* A0B9D5BE_C26E_4C02_8171_E6D4CB4813D4 */
