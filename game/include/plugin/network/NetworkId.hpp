#ifndef BE98A03E_104F_4FFB_8649_A90F635C3839
#define BE98A03E_104F_4FFB_8649_A90F635C3839

#include <functional>
#include <stddef.h>

class NetworkId;
template <>
struct std::hash<NetworkId>;

class NetworkId {
public:
    static NetworkId generate();

    NetworkId();
    NetworkId(size_t id);
    NetworkId(const NetworkId& other);
    NetworkId(NetworkId&& other);

    NetworkId& operator=(const NetworkId& rhs);
    NetworkId& operator=(NetworkId&& rhs);

    friend std::hash<NetworkId>;

    bool operator==(const NetworkId& id) const;

    size_t value() const;

private:
    static size_t m_max_id;
    size_t m_id;
};

template <>
struct std::hash<NetworkId> {
    std::size_t operator()(const NetworkId& id) const noexcept
    {
        return std::hash<size_t> {}(id.m_id);
    }
};

#endif /* BE98A03E_104F_4FFB_8649_A90F635C3839 */
