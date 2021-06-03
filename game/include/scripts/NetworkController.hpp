#ifndef E98C08FE_C6F6_43D1_931C_8BF4A5A5BC51
#define E98C08FE_C6F6_43D1_931C_8BF4A5A5BC51

#include "ige.hpp"
#include <unordered_map>

class NetworkController : public ige::plugin::script::CppBehaviour {
public:
    ige::plugin::input::InputRegistry<ige::plugin::input::KeyboardKey> inputs;
    void update() override;
};

#endif /* E98C08FE_C6F6_43D1_931C_8BF4A5A5BC51 */
