#ifndef BACKGROUNDMOVE_HPP_
#define BACKGROUNDMOVE_HPP_

#include "ige.hpp"

#include <glm/vec3.hpp>

using ige::plugin::script::CppBehaviour;
using ige::plugin::script::ScriptPlugin;
using ige::plugin::script::Scripts;

class BackgroundMove : public CppBehaviour {
public:
    BackgroundMove();
    ~BackgroundMove();

    void update() override;

protected:
private:
};

#endif /* !BACKGROUNDMOVE_HPP_ */
