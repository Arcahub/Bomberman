//
// Created by mathias on 6/2/21.
//

#ifndef BOMBERMAN_BOMB_HPP
#define BOMBERMAN_BOMB_HPP

#include "ige.hpp"
#include <chrono>

using ige::plugin::script::CppBehaviour;
using ige::plugin::script::ScriptPlugin;
using ige::plugin::script::Scripts;

class Bomb : public CppBehaviour {
public:
    void on_start() override;
    void tick() override;

protected:
private:
    std::chrono::steady_clock::time_point m_explosion_clock;
    float m_explosion_timer = 5.0f;
};

#endif // BOMBERMAN_BOMB_HPP
