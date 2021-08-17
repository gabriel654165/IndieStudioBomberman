/*
** EPITECH PROJECT, 2021
** Indie studio
** File description:
** Parser
*/

#ifndef OBJECTS_H
#define OBJECTS_H

#include "Effect.hpp"
#include "AMap.hpp"

class Objects : public AMap {
public:
    Objects(Effect &explosion);
    ~Objects();
    void setTexture();
    void drawBlock();
    void boingFunction();
    void timeManager();
    bool _hasExplode;
    Effect _explosion;
private:
    float _sphereSize;
    Model _model;
    Texture2D _texture;
    float _elapsedTime;
    float _gameDuration;
    float _explodeDuration;
    float _explodeElapsedTime;

    std::chrono::_V2::steady_clock::time_point _start;
    std::chrono::_V2::steady_clock::time_point _end;
};


#endif //OBJECTS_H
