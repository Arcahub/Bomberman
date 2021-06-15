#ifndef DD184874_3540_4D91_8A54_F109D219E008
#define DD184874_3540_4D91_8A54_F109D219E008

#include <cstring>
#include <vector>

class NetworkUtils {
public:
    template <
        typename T,
        typename std::enable_if<std::is_arithmetic<T>::value>::type* = nullptr>
    static std::vector<char> get_bytes(T const& value)
    {
        std::vector<char> bytes;

        for (size_t i = 0; i < sizeof(value); i++) {
            char byte = value >> (i * 8);

            bytes.insert(bytes.begin(), byte);
        }
        return bytes;
    }

    template <
        typename T,
        typename std::enable_if<std::is_arithmetic<T>::value>::type* = nullptr>
    static T get(std::vector<char> data)
    {
        T v = 0;

        std::reverse(data.begin(), data.end());
        memcpy(&v, data.data(), sizeof(v));
        return v;
    }

protected:
private:
};

#endif /* DD184874_3540_4D91_8A54_F109D219E008 */
