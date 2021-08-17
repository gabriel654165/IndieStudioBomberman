/*
** EPITECH PROJECT, 2024
** B_YEP_400_PAR_4_1_indiestudio_gabriel_medoukali
** File description:
** myRectangle.hpp
*/

#ifndef B_YEP_400_PAR_4_1_INDIESTUDIO_GABRIEL_MEDOUKALI_MYRECTANGLE_HPP
#define B_YEP_400_PAR_4_1_INDIESTUDIO_GABRIEL_MEDOUKALI_MYRECTANGLE_HPP

#include "ANonSelectable.hpp"

class ShapeRect final : public ANonSelectable
{
public:
    ShapeRect() = default;
    ShapeRect(Vector2 pos, Vector2 size, Color color);
    ~ShapeRect() = default;

    void setSize(float x, float y);
    void setGlobalColor(Color color);
    void setColor(Color color);
    void setOutlineColor(Color color);
    void draw() final;
    void drawR(float round);
    const Vector2 &getSize() const;
    const Color &getColor() const;
    const Color &getOutlineColor() const;
private:
    Vector2 _size;
    Color _color;
    Color _outlineColor;
};


#endif //B_YEP_400_PAR_4_1_INDIESTUDIO_GABRIEL_MEDOUKALI_MYRECTANGLE_HPP