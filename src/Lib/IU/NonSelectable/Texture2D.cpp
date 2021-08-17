/*
** EPITECH PROJECT, 2021
** Indie studio
** File description:
** Parser
*/

#include "Texture2D.hpp"

Texture2d::Texture2d(const std::string &path, Vector2 pos, float scale)
    : _path(path), _texture(LoadTexture(path.c_str())), _pos(pos), _scale(scale)
{
}

Texture2d::~Texture2d() noexcept
{
    UnloadTexture(_texture);
}

void Texture2d::draw()
{
    DrawTextureEx(_texture, _pos, 0, _scale, WHITE);
}

void Texture2d::setTexture(const std::string path)
{
    _path = path;
    _texture = LoadTexture(_path.c_str());
}

void Texture2d::setPos(Vector2 pos)
{
    _pos = pos;
}

void Texture2d::setScale(float scale)
{
    _scale = scale;
}

const Texture2D &Texture2d::getTexture() const {
    return _texture;
}

const Vector2 &Texture2d::getPos() const {
    return _pos;
}

float Texture2d::getScale() const {
    return _scale;
}
