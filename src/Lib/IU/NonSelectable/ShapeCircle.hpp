/*
** EPITECH PROJECT, 2024
** B_YEP_400_PAR_4_1_indiestudio_gabriel_medoukali
** File description:
** myCircle.hpp
*/
#ifndef B_YEP_400_PAR_4_1_INDIESTUDIO_GABRIEL_MEDOUKALI_MYCIRCLE_HPP
#define B_YEP_400_PAR_4_1_INDIESTUDIO_GABRIEL_MEDOUKALI_MYCIRCLE_HPP

#include "ANonSelectable.hpp"

class ShapeCircle final : public ANonSelectable
{
public:
    ShapeCircle();
    ShapeCircle(Vector2 pos, float radius, Color _color);
    ~ShapeCircle() = default;

    void setRadius(float radius);
    void setColor(Color color);
    void setOutlineColor(Color color);
    void draw() final;
private:
    float _radius;
    Color _color;
    Color _outlineColor;
};


#endif //B_YEP_400_PAR_4_1_INDIESTUDIO_GABRIEL_MEDOUKALI_MYCIRCLE_HPP