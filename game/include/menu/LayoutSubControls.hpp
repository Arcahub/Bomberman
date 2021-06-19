#ifndef LAYOUTSUBCONTROLS_HPP_
#define LAYOUTSUBCONTROLS_HPP_

#include "ige.hpp"

#include <glm/vec3.hpp>

using ige::plugin::script::CppBehaviour;
using ige::plugin::script::ScriptPlugin;
using ige::plugin::script::Scripts;

class LayoutSubControls : public CppBehaviour {
public:
    LayoutSubControls();
    ~LayoutSubControls();

    void update() override;

protected:
private:
};

#endif /* !LAYOUTSUBCONTROLS_HPP_ */
