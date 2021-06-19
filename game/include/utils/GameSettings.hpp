#ifndef GAMESETTINGS_HPP_
#define GAMESETTINGS_HPP_

#include "ige.hpp"

#include <glm/vec3.hpp>

using ige::plugin::script::ScriptPlugin;
using ige::plugin::script::Scripts;

class GameSettings {
public:
    GameSettings() = default;
    ~GameSettings() = default;

    float audio = 1;
    float music = 1;
    float fx = 0.7;

protected:
private:
};

#endif /* !BACKGROUNDMOVE_HPP_ */
