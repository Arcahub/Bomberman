#ifndef LAYOUTSUBDISPLAY_HPP_
#define LAYOUTSUBDISPLAY_HPP_

#include "ige.hpp"

#include <glm/vec3.hpp>

using ige::plugin::script::CppBehaviour;
using ige::plugin::script::ScriptPlugin;
using ige::plugin::script::Scripts;

class LayoutSubDisplay : public CppBehaviour {
public:
    LayoutSubDisplay();
    ~LayoutSubDisplay();

    void update() override;

protected:
private:
};

#endif /* !LAYOUTSUBAUDIO_HPP_ */
