/*
** EPITECH PROJECT, 2021
** Indie studio
** File description:
** Parser
*/

#ifndef A_SELECTABLE_HPP
#define A_SELECTABLE_HPP

#include <iostream>
#include "../AIu.hpp"

class ASelectable : public AIu {
public:
    ASelectable() = default;

    void poolEvent(Vector2 mousePos) override = 0;

    virtual void setColor() = 0;
    virtual void redirect() = 0;
    void draw() override = 0;

protected:
};

#endif //A_SELECTABLE_HPP
