/*
** EPITECH PROJECT, 2021
** Indie studio
** File description:
** Window
*/

#include "Window.hpp"
#include <iostream>

Window::Window(const int width, const int height)
{
    _height = height;
    _width = width;
    InitWindow(_width, _height, "bomberman");
}

Window::Window()
{
    _height = 1080;
    _width = 1920;
    InitWindow(_width, _height, "bomberman");
    loadingScreen();
}

Window::~Window()
{
    CloseWindow();
}

void Window::setWindowSize(const int width, const int height)
{

}

void Window::operator()(const int width, const int height)
{
    _height = height;
    _width = width;
}

void Window::setFPS(int fps)
{
    _fps = fps;
    SetTargetFPS(_fps);
}

int Window::getFPS()
{
    return _fps;
}

std::pair<int, int> Window::getWindowSize() const
{
    std::pair<int, int> pair;
    pair.first = _width;
    pair.second = _height;
    return pair;
}

void Window::loadingScreen()
{
    // Initialization
    const int screenWidth = 1920;
    const int screenHeight = 1080;
    int logoPositionX = screenWidth/2 - 128;
    int logoPositionY = screenHeight/2 - 128;
    int framesCounter = 0;
    int lettersCount = 0;
    int topSideRecWidth = 16;
    int leftSideRecHeight = 16;
    int bottomSideRecWidth = 16;
    int rightSideRecHeight = 16;
    int state = 0;
    float alpha = 1.0f;
    SetTargetFPS(60);
    while (state != 4) {
        // Update
        if (state == 0) {
            framesCounter++;
            if (framesCounter == 120) {
                state = 1;
                framesCounter = 0;
            }
        }
        else if (state == 1) {
            topSideRecWidth += 4;
            leftSideRecHeight += 4;
            if (topSideRecWidth == 256) state = 2;
        }
        else if (state == 2) {
            bottomSideRecWidth += 4;
            rightSideRecHeight += 4;
            if (bottomSideRecWidth == 256) state = 3;
        }
        else if (state == 3) {
            framesCounter++;
            if (framesCounter/12) {
                lettersCount++;
                framesCounter = 0;
            }
            if (lettersCount >= 10){
                alpha -= 0.02f;
                if (alpha <= 0.0f) {
                    alpha = 0.0f;
                    state = 4;
                }
            }
        }
        else if (state == 4) {

                framesCounter = 0;
                lettersCount = 0;
                topSideRecWidth = 16;
                leftSideRecHeight = 16;
                bottomSideRecWidth = 16;
                rightSideRecHeight = 16;
                alpha = 1.0f;
                state = 0;
        }
        // Draw
        BeginDrawing();
        ClearBackground(BLACK);
        if (state == 0) {
            if ((framesCounter/15)%2) DrawRectangle(logoPositionX, logoPositionY, 16, 16, WHITE);
        }
        else if (state == 1) {
            DrawRectangle(logoPositionX, logoPositionY, topSideRecWidth, 16, WHITE);
            DrawRectangle(logoPositionX, logoPositionY, 16, leftSideRecHeight, WHITE);
        }
        else if (state == 2) {
            DrawRectangle(logoPositionX, logoPositionY, topSideRecWidth, 16, WHITE);
            DrawRectangle(logoPositionX, logoPositionY, 16, leftSideRecHeight, WHITE);

            DrawRectangle(logoPositionX + 240, logoPositionY, 16, rightSideRecHeight, WHITE);
            DrawRectangle(logoPositionX, logoPositionY + 240, bottomSideRecWidth, 16, WHITE);
        }
        else if (state == 3) {
            DrawRectangle(logoPositionX, logoPositionY, topSideRecWidth, 16, Fade(WHITE, alpha));
            DrawRectangle(logoPositionX, logoPositionY + 16, 16, leftSideRecHeight - 32, Fade(WHITE, alpha));

            DrawRectangle(logoPositionX + 240, logoPositionY + 16, 16, rightSideRecHeight - 32, Fade(WHITE, alpha));
            DrawRectangle(logoPositionX, logoPositionY + 240, bottomSideRecWidth, 16, Fade(WHITE, alpha));

            DrawRectangle(screenWidth/2 - 112, screenHeight/2 - 112, 224, 224, Fade(BLACK, alpha));

            DrawText(TextSubtext("raylib", 0, lettersCount), screenWidth/2 - 44, screenHeight/2 + 48, 50, Fade(WHITE, alpha));
        }
        else if (state == 4)
        {
            std::string textLoading("Loading...");
            DrawText(textLoading.c_str(), (screenWidth/2) - 50, screenHeight/2, 20, WHITE);
        }

        EndDrawing();
    }
}