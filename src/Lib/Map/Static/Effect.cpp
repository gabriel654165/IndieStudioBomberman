/*
** EPITECH PROJECT, 2021
** Indie studio
** File description:
** Parser
*/

#include "Effect.hpp"
#include <ostream>
#include <iostream>

Effect::Effect()
{
    SetId();
    _timer = Timer::Instance();
    _elapsedTime = 0.0f;
    _gameDuration = 0.5f;
    _sphereSize = 0.5f;
    _position = { 1.0f, 0.0f, 7.0f };
    _hasEffectOff = false;
    state = true;
    setTexture();
}

Effect::~Effect()
{/*
    Timer::Release();
    UnloadModel(_model);
    UnloadTexture(_texture);
*/}

void Effect::timeManager()
{
    static int frames;

    _timer->Tick();
    _timer->Reset();
    _elapsedTime += _timer->DeltaTime();
    ++frames;
    if (_elapsedTime >= _gameDuration) {
        _elapsedTime = 0.0f;
        frames = 0;
        state = false;
        _hasEffectOff = true;
    }
}

void Effect::boingFunction()
{
    float incr = 0.02;

    timeManager();
    _sphereSize += incr;
}

void Effect::setTexture()
{
    _model = LoadModel("Assets/model/bomb1/uploads_files_2705643_Fireball.glb");
}

void Effect::drawAnim()
{
    boingFunction();
    if (state && _elapsedTime < _gameDuration) {
        DrawModel(_model, _position, _sphereSize, WHITE);
    }
}