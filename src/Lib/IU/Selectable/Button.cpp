/*
** EPITECH PROJECT, 2021
** Indie studio
** File description:
** Parser
*/
#include "Button.hpp"

Button::Button(std::string text, Vector2 position, Vector2 size, std::string font, int size_font, Color color, Color outline_color, std::function<void(void)> function)
{
    _text.setText(text);
    _text.setFontSize(size_font);
    _text.setFont(font.c_str());
    _text.setBoolDraw(true);
    _function = function;
    _rectangle.setPosition(position.x, position.y, 0);
    Vector2 text_size = MeasureTextEx(_text.getFont(), _text.getText().c_str(), _text.getFontSize(), (_text.getFontSize()/10));
    _rectangle.setSize(size.x, size.y);
    Vector2 text_pos = {(((_rectangle.GetPosition().x) + (_rectangle.getSize().x/2)) - (text_size.x / 2)), (((_rectangle.GetPosition().y) + (_rectangle.getSize().y/2)) - (text_size.y / 2))};
    _text.setPosition(text_pos.x, text_pos.y, 0.0f);
    _rectangle.setColor(color);
    _rectangle.setOutlineColor(outline_color);
    _text.setColor(outline_color);
}

Button::Button(std::string text, Vector2 position, Vector2 size, Font font, int size_font, Color color, Color outline_color, std::function<void(void)> function)
{
    _text.setText(text);
    _text.setFontSize(size_font);
    _text.setFont(font);
    _text.setBoolDraw(true);
    _function = function;
    _rectangle.setPosition(position.x, position.y, 0);
    Vector2 text_size = MeasureTextEx(_text.getFont(), _text.getText().c_str(), _text.getFontSize(), (_text.getFontSize()/10));
    _rectangle.setSize(size.x, size.y);
    Vector2 text_pos = {(((_rectangle.GetPosition().x) + (_rectangle.getSize().x/2)) - (text_size.x / 2)), (((_rectangle.GetPosition().y) + (_rectangle.getSize().y/2)) - (text_size.y / 2))};
    _text.setPosition(text_pos.x, text_pos.y, 0.0f);
    _rectangle.setColor(color);
    _rectangle.setOutlineColor(outline_color);
    _text.setColor(outline_color);
}

void Button::setColor()
{
}

void Button::redirect()
{
    _function();
}

void Button::update()
{
   _mousePosition = GetMousePosition();
   poolEvent(_mousePosition);
}

void Button::draw()
{
    update();
    _rectangle.drawR(10);
    _text.draw();
}

void Button::setText(const std::string& text, Vector2 pos, int fontSize, Color color)
{
    _text.setColor(color);
    _text.setFontSize(fontSize);
    _text.setText(text);
    _text.setPosition(pos.x, pos.y, 0);
}

void Button::setRectangle(Vector2 size, Color color)
{
    _rectangle.setSize(size.x, size.y);
    _rectangle.setColor(color);
}

void Button::poolEvent(Vector2 mousePos) {
    Vector3 tmp = _rectangle.GetPosition();

    if (CheckCollisionPointRec(mousePos, (Rectangle) {tmp.x, tmp.y, _rectangle.getSize().x, _rectangle.getSize().y})) {
        _rectangle.setOutlineColor(RED);
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            redirect();
        }
    }
    if (!CheckCollisionPointRec(mousePos, (Rectangle) {tmp.x, tmp.y, _rectangle.getSize().x, _rectangle.getSize().y}))
        _rectangle.setOutlineColor(WHITE);
}

const Text &Button::getText() const
{
    return _text;
}

ShapeRect &Button::getRectangle()
{
    return _rectangle;
}
