//
// Created by mathias on 6/2/21.
//

#ifndef BOMBERMAN_BOMB_HPP
#define BOMBERMAN_BOMB_HPP

#include "ige.hpp"

using ige::plugin::script::CppBehaviour;
using ige::plugin::script::ScriptPlugin;
using ige::plugin::script::Scripts;

class Bomb : public CppBehaviour {
public:
    Bomb();
    ~Bomb();

    void tick() override;

protected:
private:
};

#endif // BOMBERMAN_BOMB_HPP
