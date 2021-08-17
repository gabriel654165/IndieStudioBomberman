/*
** EPITECH PROJECT, 2021
** Indie studio
** File description:
** Window
*/

#ifndef WINDOW_H
#define WINDOW_H

#include "../ITransform.hpp"
#include "Text.hpp"
#include <utility>

#include "raylib.h"

class Window {
public:
    Window();
    Window(const int width, const int height);
    ~Window();

    void setWindowSize(const int width, const int height);
    void setFPS(int fps);
    void operator()(const int width, const int height);

    int getFPS();
    std::pair<int, int> getWindowSize() const;
private:
    void loadingScreen();
    int _fps;
    int _width;
    int _height;
};


#endif //!WINDOW_H
