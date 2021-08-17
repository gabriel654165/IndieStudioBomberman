/*
** EPITECH PROJECT, 2021
** Indie studio
** File description:
** Parser
*/

#include "IA.hpp"

IA::IA(Game &instanceGame, Vector3 position, std::shared_ptr<AnimatedModel> model)
        : Player(instanceGame, position, model)
{
    SetId();
    _status = ACTION;
    toGoValue.first = LEFT;
    nbKnownCase = 0;
    toGoValue.second = 6;
    passivMode = false;
    moveRight = false;
    moveLeft = false;
    begin = true;
    _staticPosition = _position;
    _isHuman = false;
}

void IA::SetDirection() {
    if (!_targetStack.empty()) {
        //std::cout << _targetStack.at(0).second.x << " | " << _targetStack.at(0).second.z << std::endl;
        static_cast<int>(_targetStack.at(0).second.x) < static_cast<int>(_position.x) ? xPrio = LEFT :
        static_cast<int>(_targetStack.at(0).second.x) > static_cast<int>(_position.x) ? xPrio = RIGHT : xPrio = NONE;
        static_cast<int>(_targetStack.at(0).second.z) < static_cast<int>(_position.z) ? zPrio = UP :
        static_cast<int>(_targetStack.at(0).second.z) > static_cast<int>(_position.z) ? zPrio = DOWN : zPrio = NONE;
    }
}

void IA::MoveIA()
{
    if (toGoValue.first == RIGHT) {
        if (toGoValue.second - _speed <= 0) {
            _position.x += toGoValue.second;
            _position.x = round(_position.x);
            toGoValue.second = 0;
            toGoValue.first = NONE;
            passivMode = false;
        } else {
            toGoValue.second -= _speed;
            _position.x += _speed;
        }
        _model->Animation("runRight");
    } else if (toGoValue.first == LEFT) {
        if (toGoValue.second - _speed <= 0) {
            _position.x -= toGoValue.second;
            _position.x = round(_position.x);
            toGoValue.second = 0;
            toGoValue.first = NONE;
            passivMode = false;
        } else {
            toGoValue.second -= _speed;
            _position.x -= _speed;
        }
        _model->Animation("runLeft");
    } else if (toGoValue.first == UP) {
        if (toGoValue.second - _speed <= 0) {
            _position.z -= toGoValue.second;
            _position.z = round(_position.z);
            toGoValue.second = 0;
            toGoValue.first = NONE;
            passivMode = false;
        } else {
            toGoValue.second -= _speed;
            _position.z -= _speed;
        }
        _model->Animation("runBack");
    } else if (toGoValue.first == DOWN) {
        if (toGoValue.second - _speed <= 0) {
            _position.z += toGoValue.second;
            _position.z = round(_position.z);
            toGoValue.second = 0;
            toGoValue.first = NONE;
            passivMode = false;
        } else {
            toGoValue.second -= _speed;
            _position.z += _speed;
        }
        _model->Animation("runForward");
    } else {
        _model->Animation("idle");
        passivMode = false;
    }
}

bool IA::GetLenghtWay()
{
    int xValue = 100000;
    int zValue = 100000;
    int tempX;
    int tempZ;
    int safeX;
    int safeZ;
    if (!_powerUpBomb) {
        xValue = EvaluateDirection(xPrio, _instanceGame.getBlock());
        zValue = EvaluateDirection(zPrio, _instanceGame.getBlock());
    }
    tempX = EvaluateDirection(xPrio, _instanceGame.getWall());
    tempZ = EvaluateDirection(zPrio, _instanceGame.getWall());
    safeX = (xValue < tempX) ? xValue : tempX;
    safeZ = (zValue < tempZ) ? zValue : tempZ;
    if (safeX == 1999 && safeZ == 1999) {
        toGoValue.first = NONE;
        toGoValue.second = 0.0f;
        passivMode = true;
//        if (!_targetStack.empty() && _targetStack.at(0).first == _id) {
//            _status = WAIT;
//        }
        return true;
    } else if (safeX == 0 && safeZ == 0) {
        toGoValue.first = NONE;
        toGoValue.second = 0.0f;
        passivMode = true;
        return false;
    } else {
        if (safeX == 1999) {
            toGoValue.first = zPrio;
            toGoValue.second = safeZ;
            if (toGoValue.second == 0.0f) {
                toGoValue.first = NONE;
                return false;
            }
            if (_status == WAIT)
                nbKnownCase += round(toGoValue.second);
            passivMode = true;
            return true;
        } else if (safeZ == 1999) {
            toGoValue.first = xPrio;
            toGoValue.second = safeX;
            if (_status == WAIT)
                nbKnownCase += round(toGoValue.second);
            if (toGoValue.second == 0.0f) {
                toGoValue.first = NONE;
                return false;
            }
            passivMode = true;
            return true;
        } else {
            toGoValue.first = (safeX > safeZ ? xPrio : zPrio);
            toGoValue.second = (safeX > safeZ ? safeX : safeZ);
            passivMode = true;
            nbKnownCase += round(toGoValue.second);
            return true;
        }
    }
}

bool IA::DropBomb()
{
    //std::cout << "------------" << _isDeadAlready << std::endl;
    if (!_bombPlaced || (_powerUpBomb && _bombCpt < 2) && !_isDeadAlready) {
        _bombCpt += 1;
        _instanceGame.createBomb(round(_position.x), round(_position.z), "b");
        _bombPlaced = true;
        _startPlc = std::chrono::steady_clock::now();
        knownXPriority = xPrio;
        knownZPriority = zPrio;
        return true;
    }
    return false;
}

void IA::SetPermanentTarget(std::vector<std::shared_ptr<Player>> const &playerTab, std::vector<std::shared_ptr<IA>> const &iaTab)
{
    int rand = 0;
    if (!playerTab.empty()) {
        rand = GetRandomValue(0, playerTab.size() - 1);
        _targetStack.insert(_targetStack.begin(), std::make_pair(playerTab.at(rand)->GetId(), playerTab.at(rand)->GetPosition()));
    }
    if (!iaTab.empty() && iaTab.size() > 1) {
        rand = GetRandomValue(0, iaTab.size() - 1);
        if (iaTab.at(rand)->GetId() == _id) {
            if (rand + 1 >= iaTab.size()) {
                _targetStack.insert(_targetStack.begin(), std::make_pair(iaTab.at(rand - 1)->GetId(), iaTab.at(rand - 1)->GetPosition()));
            } else {
                _targetStack.insert(_targetStack.begin(), std::make_pair(iaTab.at(rand + 1)->GetId(), iaTab.at(rand + 1)->GetPosition()));
            }
        }
    }
    if (!_instanceGame.getBonus().empty()) {
        rand = GetRandomValue(0, _instanceGame.getBonus().size() - 1);
        _targetStack.insert(_targetStack.begin(), std::make_pair(_instanceGame.getBonus().at(rand).GetId(),
                                                                 _instanceGame.getBonus().at(rand).GetPosition()));
    }
}

void IA::SetTarget(std::vector<std::shared_ptr<Player>> const &playerTab, std::vector<std::shared_ptr<IA>> const &iaTab, target status, Vector3 pos)
{
    if (status == TEMPORARY_TARGET) {
        _targetStack.insert(_targetStack.begin(), std::make_pair(_id, pos));
    }
    if (status == PERMANENT_TARGET) {
        SetPermanentTarget(playerTab, iaTab);
    }
}

void IA::CheckPermanentTarget(std::vector<std::shared_ptr<Player>> const &playerTab, std::vector<std::shared_ptr<IA>> const &iaTab)
{
    bool isAlive = false;
    for (auto it = _targetStack.begin(); it != _targetStack.end() && !_targetStack.empty();) {
        if (it->first != _id) {
            for (auto &ite : playerTab) {
                if (ite->GetId() == it->first) {
                    it->second = ite->GetPosition();
                    isAlive = true;
                }
            }
            for (auto &ite : iaTab) {
                if (ite->GetId() == it->first) {
                    it->second = ite->GetPosition();
                    isAlive = true;
                }
            }
            if (!isAlive) {
                _targetStack.erase(it);
                it = _targetStack.begin();
            } else {
                isAlive = false;
                it++;
            }
        } else
            it++;
    }
}

void IA::CheckTemporaryTarget(std::vector<std::shared_ptr<Player>> const &playerTab, std::vector<std::shared_ptr<IA>> const &iaTab)
{
    for (auto it = _targetStack.begin(); it != _targetStack.end();) {
        if (it->first == _id) {
            if (!_bombPlaced || (_powerUpBomb && _bombCpt < 2) && !_isDeadAlready) {
                _targetStack.erase(it);
                it = _targetStack.begin();
                _status = ACTION;
                nbKnownCase = 0;
            } else
                it++;
        } else
            it++;
    }
}

void IA::CheckTarget(std::vector<std::shared_ptr<Player>> const &playerTab, std::vector<std::shared_ptr<IA>> const &iaTab, target status)
{
    if (status == PERMANENT_TARGET) {
        CheckPermanentTarget(playerTab, iaTab);
    }
    if (status == TEMPORARY_TARGET) {
        CheckTemporaryTarget(playerTab, iaTab);
    }
}

void IA::CollisionEffectBonus(std::vector<std::shared_ptr<Player>> const &playerTab, std::vector<std::shared_ptr<IA>> const &iaTab)
{
    GetSpeCollision(_instanceGame.getBonus(), 0);
    if (GetSpeCollision(_instanceGame.getEffects(), 1)) {
        _isDead = true;
    }
    if (round(_position.x) == _targetStack.at(0).second.x
        && round(_position.z) == _targetStack.at(0).second.z) {
        DropBomb();
        SetTarget(playerTab, iaTab, PERMANENT_TARGET, _staticPosition);
    }
}

void IA::SetTargetFirstTime(std::vector<std::shared_ptr<Player>> const &playerTab, std::vector<std::shared_ptr<IA>> const &iaTab)
{
    if (begin) {
        SetTarget(playerTab, iaTab, PERMANENT_TARGET, _staticPosition);
        begin = false;
    }
}

void IA::MovementManager(std::vector<std::shared_ptr<Player>> const &playerTab, std::vector<std::shared_ptr<IA>> const &iaTab)
{
    SetTargetFirstTime(playerTab, iaTab);
    CheckTarget(playerTab, iaTab, PERMANENT_TARGET);
    CheckTarget(playerTab, iaTab, TEMPORARY_TARGET);
    if (!passivMode) {
        if (!_targetStack.empty())
            SetDirection();
        if (!GetLenghtWay())
            if (DropBomb())
                SetTarget(playerTab, iaTab, TEMPORARY_TARGET, _staticPosition);
        if (_status == WAIT)
            _model->Animation("idle");
        CollisionEffectBonus(playerTab, iaTab);
    } else {
        CollisionEffectBonus(playerTab, iaTab);
        MoveIA();
    }
}

void IA::resetPlayer() {
    _targetStack.clear();
    _position = _staticPosition;
    _powerUpBomb = false;
    _powerUpWall = false;
    _powerUpFire = false;
    _powerUpSpeed = false;
    health = true;
    _isDead = false;
    _isDeadAlready = false;
    begin = true;
}