/*
** EPITECH PROJECT, 2021
** Indie studio
** File description:
** Parser
*/

#ifndef BONUS_H
#define BONUS_H

#include "../../../Utils/Timer.hpp"
#include "AMap.hpp"

class Bonus : public AMap {
public:
    enum OBJ {
        BOMB,
        FIRE,
        WALL,
        SPEED,
        NONE
    };
    Bonus(OBJ elem);
    ~Bonus();
    void setTexture();
    void draw();

    void timeManager();
    void boingFunction();
    OBJ GetBonusType();
private:
    Color _color;
    float _sphereSize;
    Model _model;
    Texture2D _texture;
    OBJ _elem;

    Timer *_timer;
    float _elapsedTime;
    float _gameDuration;
};

#endif //!BONUS_H
