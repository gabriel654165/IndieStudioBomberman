/*
** EPITECH PROJECT, 2021
** Indie studio
** File description:
** Parser
*/

#ifndef IMAGE_H
#define IMAGE_H

#include "ANonSelectable.hpp"

class Texture2d : public ANonSelectable {
public:
    Texture2d() = default;
    Texture2d(const std::string &path, Vector2 pos, float scale);
    ~Texture2d();

    void draw() final;
    void setTexture(const std::string path);
    void setPos(Vector2 pos);
    const Texture2D &getTexture() const;
    const Vector2 &getPos() const;
    float getScale() const;
    void setScale(float scale);

private:
    std::string _path;
    Texture2D _texture;
    Vector2 _pos;
    float _scale;
};


#endif //IMAGE_H
