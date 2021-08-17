/*
** EPITECH PROJECT, 2024
** B_YEP_400_PAR_4_1_indiestudio_gabriel_medoukali
** File description:
** myRectangle.cpp
*/

#include "ShapeRect.hpp"

ShapeRect::ShapeRect(Vector2 pos, Vector2 size, Color color) : ANonSelectable(pos), _size(size), _color(color), _outlineColor(color)
{
}

void ShapeRect::setSize(float x, float y)
{
    _size.x = x;
    _size.y = y;
}

void ShapeRect::setColor(Color color)
{
    _color = color;
}

void ShapeRect::draw()
{
    Rectangle rect = {_pos.x, _pos.y, _size.x, _size.y};
    DrawRectangle(rect.x, rect.y, rect.width, rect.height, _color);
    DrawRectangleLines(rect.x, rect.y, rect.width, rect.height, _outlineColor);
}

void ShapeRect::drawR(float round)
{
    Rectangle rect = {_pos.x, _pos.y, _size.x, _size.y};
    DrawRectangleRounded(rect, 10, 0, _color);
    DrawRectangleRoundedLines(rect, round, 0, 5, _outlineColor);
}

void ShapeRect::setOutlineColor(Color color)
{
    _outlineColor = color;
}

void ShapeRect::setGlobalColor(Color color)
{
    _outlineColor = color;
    _color = color;
}

const Vector2 &ShapeRect::getSize() const {
    return _size;
}

const Color &ShapeRect::getColor() const {
    return _color;
}

const Color &ShapeRect::getOutlineColor() const {
    return _outlineColor;
}
