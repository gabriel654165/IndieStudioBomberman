/*
** EPITECH PROJECT, 2021
** Indie studio
** File description:
** Parser
*/

#ifndef PLAYER_H
#define PLAYER_H

#include "AnimatedModel.hpp"
#include "AMap.hpp"
#include "../../../GameManager/Game.hpp"
#include "../../../Audio/Audio.hpp"
#include <ostream>
#include <iostream>
#include <memory>
#include "rlgl.h"
#define MAXSPEED 0.1

class Player : public AMap {
public:
    explicit Player(Game &, Vector3, std::shared_ptr<AnimatedModel>);
    void PollEvent(bool);
    void draw();
    [[nodiscard]] AnimatedModel *GetModel() const;
    virtual void resetPlayer();
    template <typename T>
    bool collisionManager(T, float, float);
    virtual bool CollisionHandling();
    float GetSpeedX();
    float GetSpeedZ();
    [[nodiscard]] std::string GetName() const;
    void SetName(std::string name);
    bool GetHealth();
    bool GetDeath();
    void SetDeath(bool state);
    void SetHealth(bool state);
    bool GetIsPlaying();
    void SetIsPlaying(bool state);
    bool getExplosion();
    /*check bonus*/
    bool GetSpeedEffect();
    bool GetWallEffect();
    bool GetFireEffect();
    bool GetBombsEffect();
    bool getIsHuman() const;
    void setIsHuman(bool isHuman);
    void timeManager();
    float timeLauncher(bool effect, std::chrono::_V2::steady_clock::time_point end,
                      std::chrono::_V2::steady_clock::time_point start);
    void popBonus(Bonus target);
    void manageChronoWall();
    void manageChronoSpeed();
    void manageChronoBomb();
    void manageChronoFire();
    void manageChronoPlacedBomb();
    void manageBonus(Bonus target);
    void manageBonus(Objects target);
    void manageBonus(Effect target);
    void manageBonus(Wall target);
    void manageBonus(Block target);

    void setControls(int keyUp, int keyDown, int keyRight, int keyLeft, int keyBomb);
    void setNbControls(int nbPLayer);
protected:
    void keyPressedOnce();
    void keyPressed(bool);

    int _plNb;
    int _keyUp = KEY_UP;
    int _keyDown = KEY_DOWN;
    int _keyRight = KEY_RIGHT;
    int _keyLeft = KEY_LEFT;
    int _keyBomb = KEY_SPACE;

    std::string _name;
    bool moveRight;
    bool moveLeft;
    bool state;
    bool isTrigger;
    bool _isDead;
    bool _isDeadAlready;
    int health;
    bool _isPlaying;
    bool _isHuman;
protected:
    float _speed;
    /*POWERUPS*/
    std::chrono::_V2::steady_clock::time_point _startPlc;
    std::chrono::_V2::steady_clock::time_point _endPlc;
    float _elapsedTimePlc;
    float _effectDurationPlc;
    bool _bombPlaced;
    int _bombCpt;
    bool _bomb_explosion;

    std::chrono::_V2::steady_clock::time_point _startS;
    std::chrono::_V2::steady_clock::time_point _startW;
    std::chrono::_V2::steady_clock::time_point _endW;
    std::chrono::_V2::steady_clock::time_point _endS;
    std::chrono::_V2::steady_clock::time_point _startF;
    std::chrono::_V2::steady_clock::time_point _startB;
    std::chrono::_V2::steady_clock::time_point _endF;
    std::chrono::_V2::steady_clock::time_point _endB;
    float _elapsedTimeSpeed;
    float _effectDurationSpeed;
    float _elapsedTimeWall;
    float _effectDurationWall;
    float _elapsedTimeFire;
    float _effectDurationFire;
    float _elapsedTimeBomb;
    float _effectDurationBomb;

    bool _powerUpSpeed;
    bool _powerUpWall;
    bool _powerUpFire;
    bool _powerUpBomb;
    Game &_instanceGame;
    std::shared_ptr<AnimatedModel> _model;
};

template <typename T>
bool Player::collisionManager(T target, float speedX, float speedZ)
{
    for (auto it = target.begin(); it != target.end(); it++) {
        if (CheckCollisionBoxes((BoundingBox) {(Vector3) {(_position.x + speedX) - 0.3f, _position.y - 0.3f, (_position.z + speedZ) - 0.3f},
                                           (Vector3) {(_position.x + speedX) + 0.3f, _position.y + 0.3f, (_position.z + speedZ) + 0.3f}},
                            (BoundingBox) {(Vector3) {static_cast<AMap>(*it).GetPosition().x - 0.5f, static_cast<AMap>(*it).GetPosition().y - 0.5f, static_cast<AMap>(*it).GetPosition().z - 0.5f},
                                           (Vector3) {static_cast<AMap>(*it).GetPosition().x + 0.5f, static_cast<AMap>(*it).GetPosition().y + 0.5f, static_cast<AMap>(*it).GetPosition().z + 0.5f}})) {
            manageBonus(*it);
            return true;
        }
    }
    return false;
}

#endif //PLAYER_H
