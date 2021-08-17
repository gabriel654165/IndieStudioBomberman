/*
** EPITECH PROJECT, 2021
** Indie studio
** File description:
** Parser
*/

#ifndef TEXT_H
#define TEXT_H

#include "ANonSelectable.hpp"

class Text : public ANonSelectable {
public:
    Text() = default;
    Text(Vector2 pos, std::string text, int fontSize, std::string font, Color color, bool center);
    Text(Vector2 pos, std::string text, int fontSize, Font font, Color color, bool center);
    ~Text();

    void setText(std::string text);
    void setFontSize(int fontSize);
    void setFontSize(int fontSize, bool center);
    void setColor(Color color);
    void setFont(std::string path);
    void setFont(Font font);
    void setBoolDraw(bool draw);
    void draw() final;
    [[nodiscard]] const std::string &getText() const;
    [[nodiscard]] int getFontSize() const;
    Font getFont();
    [[nodiscard]] const Color &getColor() const;
    bool getBoolDraw() const;


private:
    std::string _text;
    int _fontSize;
    Color _color;
    Font _font;
    bool _center;
    bool _draw;
};

#endif //TEXT_H