/*
** EPITECH PROJECT, 2021
** Indie studio
** File description:
** Parser
*/

#include "AMap.hpp"

void AMap::setPosition(float x, float y, float z)
{
    _position = (Vector3){x, y, z};
}

Vector3 AMap::GetPosition() const
{
    return(_position);
}

void AMap::setRotation(float x, float y, float z)
{
    _rotation = (Vector3){x, y, z};
}

Vector3 AMap::GetRotation() const
{
    return (_rotation);
}

void AMap::setState(bool new_state)
{
    state = new_state;
}

bool AMap::GetState() const
{
    return (state);
}

void AMap::SetId()
{
    _id = (unsigned long)this;
}

unsigned long AMap::GetId() const
{
    return _id;
}

Vector3 AMap::GetScale() const
{
    return _scale;
}