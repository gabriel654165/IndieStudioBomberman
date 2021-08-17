/*
** EPITECH PROJECT, 2021
** Indie studio
** File description:
** Parser
*/

#ifndef WALL_HPP
#define WALL_HPP

#include "AMap.hpp"

class Wall : public AMap {
public:
    Wall();
    ~Wall();
    void setTexture(Texture2D texture);
    void drawBlock();
private:
    Texture2D _texture;
    Vector3 _size;
};


#endif //WALL_HPP
