/*
** EPITECH PROJECT, 2021
** Indie studio
** File description:
** Parser
*/

#include "Objects.hpp"
#include <ostream>
#include <iostream>
#include <unordered_map>

Objects::Objects(Effect &explosion)
    : _explosion(explosion)
{
    SetId();
    _start = std::chrono::steady_clock::now();
    _elapsedTime = 0.0f;
    _gameDuration = 3.21f;
    _explodeDuration = 4.0f;
    _explodeElapsedTime = 0.0f;
    state = true;
    _hasExplode = false;
    _sphereSize = 0.007f;
    _position = { 1.0f, 0.0f, 7.0f };
    setTexture();
}

Objects::~Objects()
{/*
    delete _explosion;
    UnloadModel(_model);
    UnloadTexture(_texture);
*/}

void Objects::setTexture()
{
    _model = LoadModel("Assets/model/bomberman_bomb/scene.gltf");
    _texture = LoadTexture("Assets/model/bomberman_bomb/textures/Bomb_diffuse.png");
    _model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = _texture;
}

void Objects::timeManager()
{
    _end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = _end - _start;
    _start = std::chrono::steady_clock::now();

    _elapsedTime += elapsed_seconds.count();
    _explodeElapsedTime += elapsed_seconds.count();

    if (_elapsedTime >= _gameDuration) {
        elapsed_seconds.zero();
        _start = std::chrono::steady_clock::now();
        _elapsedTime = 0.0f;
        state = false;
        _sphereSize = 0.005f;
        _explosion.setState(true);
        _hasExplode = true;
    }
}

void Objects::boingFunction()
{
    float incr = 0.0001f;

    timeManager();
    if ((_elapsedTime >= 0 && _elapsedTime < 0.5)
        || (_elapsedTime >= 1 && _elapsedTime < 1.5)
        || (_elapsedTime >= 2 && _elapsedTime < 2.5)
        || (_elapsedTime >= 3 && _elapsedTime < 3.5)) {
        _sphereSize += incr;
    } else if ((_elapsedTime >= 0.5 && _elapsedTime < 1)
        || (_elapsedTime >= 1.5 && _elapsedTime < 2)
        ||  (_elapsedTime >= 2.5 && _elapsedTime < 3)
        || (_elapsedTime >= 3.5 && _elapsedTime < 4) ) {
        _sphereSize -= incr;
    }
}

void Objects::drawBlock()
{
    boingFunction();

    if (state) {
        DrawModel(_model, _position, _sphereSize, WHITE);
    } else if (_explosion.GetState()) {
        _explosion.setPosition(_position.x, _position.y, _position.z);
        _explosion.drawAnim();//timer
    }
}