#ifndef DB1A509F_9414_41CF_914D_1E5BF31835F3
#define DB1A509F_9414_41CF_914D_1E5BF31835F3

#include "ige.hpp"

class BombermanLobbyPlugin : public ige::core::App::Plugin {
public:
    BombermanLobbyPlugin(bool is_client)
    {
        m_is_client = is_client;
    }
    bool m_is_client;

    void plug(ige::core::App::Builder&) const override;
};

#endif /* DB1A509F_9414_41CF_914D_1E5BF31835F3 */
