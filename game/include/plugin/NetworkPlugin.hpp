#ifndef B2F0FEE4_07E1_4440_8E20_2CE0395BE26D
#define B2F0FEE4_07E1_4440_8E20_2CE0395BE26D

#include "ige.hpp"
#include "network/NetworkManager.hpp"

class NetworkPlugin : public ige::core::App::Plugin {
public:
    void plug(ige::core::App::Builder&) const override;
};

#endif /* B2F0FEE4_07E1_4440_8E20_2CE0395BE26D */
