/*
** EPITECH PROJECT, 2021
** Indie studio
** File description:
** Scene
*/

#include "Cam.hpp"
#include <iostream>

Cam::Cam()
{
    _state = true;
    _camera = { 0 };
    _camera.position = (Vector3){ 10.0f, 20.0f, 10.0f };
    _camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    _camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    _camera.fovy = 45.0f;
    _camera.projection = CAMERA_PERSPECTIVE;
}

Cam::~Cam()
{
}

void Cam::setPosition(float x, float y, float z)
{
    _camera.position = (Vector3){ x, y, z };
}

void Cam::setRotation(float x, float y, float z)
{
    _camera.target = (Vector3){ x, y, z };
}

void Cam::setCameraMode(int cameraMode)
{
    _cameraMode = cameraMode;
    SetCameraMode(_camera, cameraMode);
}

void Cam::setState(bool state)
{
    _state = state;
}

Vector3 Cam::GetPosition() const
{
    Vector3 vec = {_camera.position.x, _camera.position.y, _camera.position.z};
    return vec;
}

Vector3 Cam::GetRotation() const
{
    return _camera.target;
}

int Cam::GetCameraMode()
{
    return _cameraMode;
}

bool Cam::GetState() const
{
    return true;
}

Camera &Cam::getCamera()
{
    return _camera;
}

void Cam::poolEvent()
{
    if (IsKeyDown(KEY_F1) && _camera.position.y < 28)
        _camera.position.y += 0.1f;
    if (IsKeyDown(KEY_F2) && _camera.position.y > 13)
        _camera.position.y -= 0.1f;
    if (IsKeyDown(KEY_F3) && _camera.position.x > -45)
        _camera.position.x -= 0.1f;
    if (IsKeyDown(KEY_F4) && _camera.position.x < 10)
        _camera.position.x += 0.1f;
}

void Cam::updateCamera()
{
    poolEvent();
    UpdateCamera(&_camera);
}

Vector3 Cam::GetScale() const {
    return _scale;
}
