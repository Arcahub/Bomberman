/*
** EPITECH PROJECT, 2021
** SoloController
** File description:
** SoloController
*/

#ifndef SOLOCONTROLLER_HPP_
#define SOLOCONTROLLER_HPP_

#include "glm/vec2.hpp"
#include "ige.hpp"

using ige::plugin::script::CppBehaviour;
using ige::plugin::script::ScriptPlugin;
using ige::plugin::script::Scripts;

#include <iostream>

class SoloController : public CppBehaviour {
public:
    SoloController();
    ~SoloController();

    void tick() override;

    void SetSoloMovement(ige::plugin::input::InputManager* input);

    glm::vec2 m_direction { 0.0f };
    bool m_bomb = false;

protected:
private:
};

#endif /* !SOLOCONTROLLER_HPP_ */
