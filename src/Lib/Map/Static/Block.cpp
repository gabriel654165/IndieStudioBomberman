/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-gabriel.medoukali
** File description:
** Block
*/

#include "Block.hpp"

Block::Block()
{
    _size = (Vector3){1.0f, 1.0f, 1.0f};
}

Block::~Block()
{/*
    UnloadTexture(_texture);
*/}

void Block::setTexture(Texture2D texture)
{
    _texture = texture;
}

void Block::drawBlock()
{
    DrawCubeTexture(_texture, _position, _size.x, _size.y, _size.z, WHITE);
}