/*
** EPITECH PROJECT, 2021
** Indie studio
** File description:
** Parser
*/

#include "Text.hpp"

Text::Text(Vector2 pos, std::string text, int fontSize, std::string font, Color color, bool center)
{
    _text = text;
    _font = LoadFont(font.c_str());
    _color = color;
    _fontSize = fontSize;
    _center = center;
    _draw = true;
    if (center) {
        Vector2 textSize = MeasureTextEx(_font, text.c_str(), _fontSize, _fontSize/10);
        setPosition((pos.x - (textSize.x /2)), (pos.y - (textSize.y / 2)), 0);
    } else {
        setPosition(pos.x, pos.y, 0);
    }
}

Text::Text(Vector2 pos, std::string text, int fontSize, Font font, Color color, bool center)
{
    _text = text;
    _font = font;
    _color = color;
    _fontSize = fontSize;
    _center = center;
    _draw = true;
    if (center) {
        Vector2 textSize = MeasureTextEx(_font, text.c_str(), _fontSize, _fontSize/10);
        setPosition((pos.x - (textSize.x /2)), (pos.y - (textSize.y / 2)), 0);
    } else {
        setPosition(pos.x, pos.y, 0);
    }
}

Text::~Text() noexcept
{
}

void Text::setText(std::string text)
{
    _text = text;
}

void Text::setFontSize(int fontSize, bool center)
{
    if (_fontSize == fontSize)
        return;
    _fontSize = fontSize;

    Vector2 textSize = MeasureTextEx(_font, _text.c_str(), _fontSize, _fontSize / 10);
    setPosition((_pos.x - (textSize.x / 200)), (_pos.y - (textSize.y / 200)), 0);
}

void Text::setFontSize(int fontSize)
{
    _fontSize = fontSize;
}

void Text::setColor(Color color)
{
    _color = color;
}

Font Text::getFont()
{
    return (_font);
}

void Text::draw()
{
    if (_draw == true)
        DrawTextEx(_font, _text.c_str(), _pos, (float)_fontSize, (float)_fontSize/10, _color);
}

const std::string &Text::getText() const
{
    return _text;
}

int Text::getFontSize() const
{
    return _fontSize;
}

const Color &Text::getColor() const
{
    return _color;
}

void Text::setFont(std::string path)
{
    _font = LoadFont(path.c_str());
}

void Text::setFont(Font font)
{
    _font = font;
}

void Text::setBoolDraw(bool draw)
{
    _draw = draw;
}

bool Text::getBoolDraw() const
{
    return (_draw);
}
