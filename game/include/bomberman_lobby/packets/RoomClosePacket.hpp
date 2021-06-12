#ifndef F0CB50E9_7A73_45F1_9BCA_2B61B69A1A72
#define F0CB50E9_7A73_45F1_9BCA_2B61B69A1A72

#include <vector>

class RoomClosePacket {
public:
    std::vector<char> serialize();
    void serialize(std::vector<char>& buff);
    static RoomClosePacket deserialize(const std::vector<char>& data);
};

#endif /* F0CB50E9_7A73_45F1_9BCA_2B61B69A1A72 */
