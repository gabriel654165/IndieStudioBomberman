/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-gabriel.medoukali
** File description:
** InputBox
*/

#include "InputBox.hpp"

InputBox::InputBox(Vector2 pos, Vector2 size, std::string font, int font_size, int char_max, Color color, Color outline_color, std::function<void(void)> function)
{
    _pos = pos;
    _size = size;
    _font = LoadFont(font.c_str());
    _font_size = font_size;
    _color = color;
    _outlineColor = outline_color;
    _function = function;
    _rect = {_pos.x, _pos.y, _size.x, _size.y};
    _char_max = char_max;

    mouseOnText = false;
    framesCounter = 0;
    letterCount = 0;
}

InputBox::InputBox(Vector2 pos, Vector2 size, Font font, int font_size, int char_max, Color color, Color outline_color, std::function<void(void)> function)
{
    _pos = pos;
    _size = size;
    _font = font;
    _font_size = font_size;
    _color = color;
    _outlineColor = outline_color;
    _function = function;
    _rect = {_pos.x, _pos.y, _size.x, _size.y};
    _char_max = char_max;

    mouseOnText = false;
    framesCounter = 0;
    letterCount = 0;
}

void InputBox::redirect()
{
    _function();
}

void InputBox::SetText(std::string newName)
{
    _text = newName;
}

void InputBox::draw()
{
    update();
    DrawRectangleRec(_rect, GRAY);
    if (mouseOnText)
        DrawRectangleLines(_rect.x, _rect.y, _rect.width, _rect.height, RED);
    else
        DrawRectangleLines(_rect.x, _rect.y, _rect.width, _rect.height, DARKGRAY);
    DrawTextEx(_font, _text.c_str(),(Vector2) {_rect.x + 8, _rect.y + 8}, _font_size, _font_size/10, WHITE);
    if (mouseOnText) {
        if (letterCount < _char_max) {
            if (((framesCounter/20)%2) == 0)
                DrawTextEx(_font, "_", (Vector2) {_rect.x + 8 + MeasureText(_text.c_str(), _font_size), _rect.y + 12}, _font_size, _font_size/10, WHITE);
        }
    }
}

std::string InputBox::GetText() const
{
    return _text;
}

void InputBox::setColor()
{
}

void InputBox::update()
{
    char key;

    if (CheckCollisionPointRec(GetMousePosition(), _rect))
        mouseOnText = true;
    else
        mouseOnText = false;

    if (mouseOnText) {
        SetMouseCursor(MOUSE_CURSOR_IBEAM);
        key = GetCharPressed();
            if (key >= 32 && key <= 122) {
                if (letterCount < _char_max) {
                    _text.push_back(key);
                    letterCount++;
                }
            }
            if (IsKeyPressed(KEY_BACKSPACE))
            {
                if (!_text.empty()) {
                    letterCount--;
                    _text.pop_back();
                }
            }
        }
        else
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);

        if (mouseOnText)
            framesCounter++;
        else
            framesCounter = 0;
}

void InputBox::poolEvent(Vector2 mousePos)
{
}