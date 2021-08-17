/*
** EPITECH PROJECT, 2021
** Indie studio
** File description:
** Parser
*/

#ifndef EFFECT_H
#define EFFECT_H

#include "../../../Utils/Timer.hpp"
#include "AMap.hpp"

class Effect : public AMap {
public:
    Effect();
    ~Effect();
    void setTexture();
    void drawAnim();
    void timeManager();
    void boingFunction();
    bool _hasEffectOff;
private:
    float _sphereSize;
    Model _model;
    Texture2D _texture;

    Timer *_timer;
    float _elapsedTime;
    float _gameDuration;
};


#endif //!EFFECT_H
