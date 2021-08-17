/*
** EPITECH PROJECT, 2021
** Indie studio
** File description:
** Parser
*/

#include "Wall.hpp"

Wall::Wall()
{
    _size = (Vector3){1.0f, 1.0f, 1.0f};
}

Wall::~Wall()
{/*
    UnloadTexture(_texture);
*/}

void Wall::setTexture(Texture2D texture)
{
    _texture = texture;
}

void Wall::drawBlock()
{
    DrawCubeTexture(_texture, _position, _size.x, _size.y, _size.z, WHITE);
}