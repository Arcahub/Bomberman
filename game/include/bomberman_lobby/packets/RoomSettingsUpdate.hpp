#ifndef E2C7DE35_8A75_4BF7_8E23_FC6C34B7D4B7
#define E2C7DE35_8A75_4BF7_8E23_FC6C34B7D4B7

#include <vector>

class RoomSettingsUpdatePacket {
public:
    std::vector<char> serialize();
    void serialize(std::vector<char>& buff);
    static RoomSettingsUpdatePacket deserialize(const std::vector<char>& data);
};

#endif /* E2C7DE35_8A75_4BF7_8E23_FC6C34B7D4B7 */
