/*
** EPITECH PROJECT, 2021
** Indie studio
** File description:
** Parser
*/

#include "AIu.hpp"

AIu::AIu(Vector2 pos) : _pos(pos)
{
}


AIu::~AIu()
{

}

void AIu::setPosition(float x, float y, float z)
{
    (void)z;
    _pos.x = x;
    _pos.y = y;
}

Vector3 AIu::GetPosition() const
{
    return ((Vector3) {_pos.x, _pos.y, 0});
}

void AIu::setRotation(float x, float y, float z)
{

}

Vector3 AIu::GetRotation() const
{
    Vector3 vec = {0,0,0};
    return vec;
}

void AIu::setState(bool state)
{
    _state = state;
}

bool AIu::GetState() const
{
    return (_state);
}

Vector3 AIu::GetScale() const {
    return _scale;
}
