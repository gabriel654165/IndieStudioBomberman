/*
** EPITECH PROJECT, 2021
** Indie studio
** File description:
** Parser
*/

#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <iostream>
#include <functional>

#include "ASelectable.hpp"
#include "Text.hpp"
#include "ShapeRect.hpp"

class Button : public ASelectable {
public:
    Button() = default;
    ~Button() = default;
    Button(std::string text, Vector2 position, Vector2 size, std::string font, int size_font, Color color, Color outline_color, std::function<void(void)> function);
    Button(std::string text, Vector2 position, Vector2 size, Font font, int size_font, Color color, Color outline_color, std::function<void(void)> function);
    void setColor() override;
    void redirect() override;
    void setText(const std::string& text, Vector2 pos, int fontSize, Color color);
    void setRectangle(Vector2 size, Color color);
    void draw() final;
    void poolEvent(Vector2 mousePos) final;
    void update();
    const Text &getText() const;
    ShapeRect &getRectangle();

private:
    Text _text;
    ShapeRect _rectangle;
    std::function<void(void)> _function;
    Vector2 _mousePosition;
};

#endif //BUTTON_HPP
