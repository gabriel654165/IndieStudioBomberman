/*
** EPITECH PROJECT, 2021
** Indie studio
** File description:
** Parser
*/

#include "Bonus.hpp"
#include <iostream>

Bonus::Bonus(OBJ elem)
{
    SetId();
    _timer = Timer::Instance();
    _elapsedTime = 0.0f;
    _gameDuration = 1.0f;

    _elem = elem;
    _sphereSize = 0.50f;
    _position = { -1.0f, 0.0f, 1.0f };

    setTexture();
}

Bonus::~Bonus()
{/*
    UnloadModel(_model);
    UnloadTexture(_texture);
*/}

Bonus::OBJ Bonus::GetBonusType()
{
    return _elem;
}

void Bonus::timeManager()
{
    static int frames;
    int reset = 1;

    _timer->Tick();
    _timer->Reset();
    _elapsedTime += _timer->DeltaTime();
    if (_elapsedTime >= _gameDuration) {
        _timer->Reset();
        _elapsedTime = 0.0f;
        _position.y = 0.0f;
        _position = (Vector3){_position.x, _position.y, _position.z};
        frames = 0;
    }
}

void Bonus::boingFunction()
{
    float incr = 0.015;

    if (_elapsedTime >= 0 && _elapsedTime < _gameDuration/2) {
        _position.y += incr;
        _position = (Vector3){_position.x, _position.y, _position.z};
    } else {
        _position.y -= incr;
        _position = (Vector3){_position.x, _position.y, _position.z};
    }
    timeManager();
}

void Bonus::setTexture()
{
    std::string path;
    if (_elem == BOMB) {
        _color = RED;
    } else if (_elem == FIRE) {
        _color = ORANGE;
    } else if (_elem == WALL) {
        _color = GREEN;
    } else if (_elem == SPEED) {
        _color = BLUE;
    }
    _model = LoadModelFromMesh(GenMeshSphere(0.5f, 32, 32));
}

void Bonus::draw()
{
    boingFunction();
    //DrawModelEx(_model, _spherePos, (Vector3){0.0, 0.0, 0.0}, 0.0f, (Vector3){1.0f, 1.0f, 1.0f}, WHITE);
    DrawModel(_model, _position, _sphereSize, _color);
}