/*
** EPITECH PROJECT, 2021
** Indie studio
** File description:
** Parser
*/

#ifndef A_NON_SELECTABLE_HPP
#define A_NON_SELECTABLE_HPP

#include <iostream>
#include "../AIu.hpp"

class ANonSelectable : public AIu {
public:
    ANonSelectable() = default;
    explicit ANonSelectable(Vector2 pos);
    ~ANonSelectable() = default;

    void poolEvent(Vector2 mousePos) final;
    void draw() override = 0;
    //void setPos(float posX, float posY);
private:
};

#endif //A_NON_SELECTABLE_HPP
