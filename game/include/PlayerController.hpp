/*
** EPITECH PROJECT, 2021
** PlayerController
** File description:
** PlayerController
*/

#ifndef PLAYERCONTROLLER_HPP_
#define PLAYERCONTROLLER_HPP_

#include "ige.hpp"

using ige::plugin::script::CppBehaviour;
using ige::plugin::script::ScriptPlugin;
using ige::plugin::script::Scripts;

class PlayerController : public CppBehaviour {
    public:
        PlayerController();
        ~PlayerController();

        void tick() override;
    protected:
    private:
};

#endif /* !PLAYERCONTROLLER_HPP_ */
