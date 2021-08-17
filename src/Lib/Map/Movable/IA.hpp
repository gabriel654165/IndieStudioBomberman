/*
** EPITECH PROJECT, 2021
** Indie studio
** File description:
** Parser
*/

#ifndef IA_H
#define IA_H

#include "Player.hpp"
#include "../../../GameManager/Game.hpp"
#include <ostream>
#include <iostream>
#include <cmath>
#include <iomanip>

enum statusIa {
    WAIT,
    ACTION
};

enum target {
    PERMANENT_TARGET,
    TEMPORARY_TARGET
};

enum Priority {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    ERROR_TARGET,
    NONE
};

class IA : public Player {
public:
    IA(Game &, Vector3, std::shared_ptr<AnimatedModel>);
    void MovementManager(std::vector<std::shared_ptr<Player>> const &, std::vector<std::shared_ptr<IA>> const &);
    void resetPlayer() override;
private:
    void SetTargetFirstTime(std::vector<std::shared_ptr<Player>> const &, std::vector<std::shared_ptr<IA>> const &);
    void CheckPermanentTarget(std::vector<std::shared_ptr<Player>> const &, std::vector<std::shared_ptr<IA>> const &);
    void CheckTemporaryTarget(std::vector<std::shared_ptr<Player>> const &, std::vector<std::shared_ptr<IA>> const &);
    void CheckTarget(std::vector<std::shared_ptr<Player>> const &, std::vector<std::shared_ptr<IA>> const &, target);
    void SetTarget(std::vector<std::shared_ptr<Player>> const &, std::vector<std::shared_ptr<IA>> const &, target, Vector3);
    bool GetLenghtWay();
    bool DropBomb();
    void SetPermanentTarget(std::vector<std::shared_ptr<Player>> const &, std::vector<std::shared_ptr<IA>> const &);
    template <typename T>
    int EvaluateDirection(Priority, T);
    void SetDirection();
    void MoveIA();
    template <typename T>
    bool GetSpeCollision(T, int);
    void CollisionEffectBonus(std::vector<std::shared_ptr<Player>> const &, std::vector<std::shared_ptr<IA>> const &);

    bool passivMode;
    std::vector<std::pair<unsigned long, Vector3>> _targetStack;
    Priority xPrio;
    Priority zPrio;
    statusIa _status;
    std::pair<Priority, float> toGoValue;
    Vector3 _staticPosition;
    Priority knownXPriority;
    Priority knownZPriority;
    int nbKnownCase;
    bool begin;
};

template <typename T>
bool IA::GetSpeCollision(T tab, int spe)
{
    for (auto it = tab.begin(); it != tab.end(); it++) {
        if (it->GetPosition().x == round(_position.x)
            && it->GetPosition().z == round(_position.z)) {
            if (spe == 0)
                manageBonus(*it);
            return true;
        }
    }
    return false;
}

template <typename T>
int IA::EvaluateDirection(Priority safeDir, T tabToEvaluate)
{
    if (safeDir == RIGHT) {
        for (auto &it : tabToEvaluate) {
            if (static_cast<AMap>(it).GetPosition().z == round(_position.z)
                && static_cast<int>(static_cast<AMap>(it).GetPosition().x) > _position.x)
                return static_cast<int>(std::abs(static_cast<AMap>(it).GetPosition().x - _position.x) - 1.0f);
        }
    } else if (safeDir == LEFT) {
        for (auto it = tabToEvaluate.rbegin(); it != tabToEvaluate.rend(); it++) {
            if (static_cast<AMap>(*it).GetPosition().z == round(_position.z)
                && static_cast<AMap>(*it).GetPosition().x < _position.x) {
                return static_cast<int>(std::abs(static_cast<AMap>(*it).GetPosition().x - _position.x) - 1.0f);
            }
        }
    } else if (safeDir == UP) {
        for (auto it = tabToEvaluate.rbegin(); it != tabToEvaluate.rend(); it++) {
            if (static_cast<AMap>(*it).GetPosition().z < _position.z
                && static_cast<AMap>(*it).GetPosition().x == round(_position.x)) {
                return static_cast<int>(std::abs(static_cast<AMap>(*it).GetPosition().z - _position.z) - 1.0f);
            }
        }
    } else if (safeDir == DOWN) {
        for (auto &it : tabToEvaluate) {
            if (static_cast<AMap>(it).GetPosition().x == round(_position.x)
                && static_cast<int>(static_cast<AMap>(it).GetPosition().z) > _position.z)
                return static_cast<int>(std::abs(static_cast<AMap>(it).GetPosition().z - _position.z) - 1.0f);
        }
    }
    return 1999;
}

#endif
