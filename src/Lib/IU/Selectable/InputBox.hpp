/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-gabriel.medoukali
** File description:
** InputBox
*/

#ifndef INPUTBOX_HPP_
#define INPUTBOX_HPP_

#include <functional>

#include "ASelectable.hpp"

class InputBox : public ASelectable {
    public:
        InputBox() = default;
        ~InputBox() = default;
        InputBox(Vector2 pos, Vector2 size, std::string font, int font_size, int char_max, Color color, Color outline_color, std::function<void(void)> function);
        InputBox(Vector2 pos, Vector2 size, Font font, int font_size, int char_max, Color color, Color outline_color, std::function<void(void)> function);
        void redirect() override;
        void setColor() override;
        void draw() final;
        void poolEvent(Vector2 mousePos) final;
        void update();
        std::string GetText() const;
        void SetText(std::string newName);
    private:
        std::string _text = "Player";
        std::function<void(void)> _function;
        Vector2 _mousePosition;
        Vector2 _size;
        Font _font;
        int _font_size;
        Color _color;
        Color _outlineColor;
        Rectangle _rect;

        char *_char_text;
        char name[9 + 1];
        bool mouseOnText;
        int framesCounter;
        int letterCount;
        int _char_max;
};

#endif /* !INPUTBOX_HPP_ */
