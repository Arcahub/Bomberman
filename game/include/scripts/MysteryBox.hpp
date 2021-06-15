#ifndef MYSTERYBOX_HPP_
#define MYSTERYBOX_HPP_

#include "ige.hpp"

#include <glm/vec3.hpp>

using ige::plugin::script::CppBehaviour;
using ige::plugin::script::ScriptPlugin;
using ige::plugin::script::Scripts;

class MysteryBox : public CppBehaviour {
public:
    MysteryBox();
    ~MysteryBox();

    void update() override;

protected:
private:
};

#endif /* !MYSTERYBOX_HPP_ */
