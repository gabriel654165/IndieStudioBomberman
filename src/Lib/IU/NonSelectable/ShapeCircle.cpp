/*
** EPITECH PROJECT, 2024
** B_YEP_400_PAR_4_1_indiestudio_gabriel_medoukali
** File description:
** myCircle.cpp
*/

#include "ShapeCircle.hpp"

ShapeCircle::ShapeCircle()
{

}

ShapeCircle::ShapeCircle(Vector2 pos, float radius, Color color) : ANonSelectable(pos), _radius(radius), _color(color),
                                                                    _outlineColor(color)
{
}

void ShapeCircle::setRadius(float radius)
{
    _radius = radius;
}

void ShapeCircle::setColor(Color color)
{
    _color = color;
}

void ShapeCircle::draw()
{
    DrawCircleV(_pos, _radius, _color);
    DrawCircleLines(_pos.x, _pos.y, _radius, _outlineColor);
}

void ShapeCircle::setOutlineColor(Color color)
{
    _outlineColor = color;
}
