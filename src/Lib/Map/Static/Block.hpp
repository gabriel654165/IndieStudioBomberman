/*
** EPITECH PROJECT, 2021
** Indie studio
** File description:
** Parser
*/

#ifndef BLOCK_H
#define BLOCK_H

#include "AMap.hpp"

class Block : public AMap {
public:
    Block();
    ~Block();
    void setTexture(Texture2D texture);
    void drawBlock();

private:
    Texture2D _texture;
    Vector3 _size;
};


#endif //BLOCK_H
