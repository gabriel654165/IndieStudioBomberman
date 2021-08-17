/*
** EPITECH PROJECT, 2021
** Indie studio
** File description:
** Parser
*/

#include "Player.hpp"

Player::Player(Game &instanceGame, Vector3 position, std::shared_ptr<AnimatedModel> model)
        : _instanceGame(instanceGame), _model(model)
{
    SetId();
    setPosition(position.x, position.y, position.z);
    moveRight = false;
    moveLeft = false;
    _isDead = false;
    _isDeadAlready = false;
    _speed = 0.1f;
    _isPlaying = true;
    _isHuman = true;
    _bombPlaced = false;
    _elapsedTimePlc = 0.0f;
    _effectDurationPlc = 3.21f;
    _bombCpt = 0;
    /*EFFECTS*/
    _powerUpWall = false;
    _powerUpSpeed = false;
    _powerUpFire = false;
    _powerUpBomb = false;
    _elapsedTimeFire = 0.0f;
    _effectDurationFire = 5.0f;
    _elapsedTimeBomb = 0.0f;
    _effectDurationBomb = 10.0f;
    _elapsedTimeSpeed = 0.0f;
    _effectDurationSpeed = 5.0f;
    _elapsedTimeWall = 0.0f;
    _effectDurationWall = 5.0f;
    _position = position;
    _bomb_explosion = false;
    /*!EFFECTS*/
}

void Player::draw()
{
    timeManager();
    manageChronoSpeed();
    manageChronoWall();
    manageChronoBomb();
    manageChronoFire();
    manageChronoPlacedBomb();
    if (!_isDeadAlready || (_isPlaying && !_isDeadAlready)) {
        DrawModelEx(_model->GetModel(), _position, (Vector3) {-1.0f, 0.0f, 0.0f}, 90.0f, _model->GetScale(), WHITE);
    }
}

void Player::setControls(int keyUp, int keyDown, int keyRight, int keyLeft, int keyBomb)
{
    _keyUp = keyUp;
    _keyDown = keyDown;
    _keyRight = keyRight;
    _keyLeft = keyLeft;
    _keyBomb = keyBomb;
}

void Player::setNbControls(int nbPLayer)
{
    _plNb = nbPLayer;
    if (_plNb == 0) {
        _keyUp = KEY_W;
        _keyDown = KEY_S;
        _keyRight = KEY_D;
        _keyLeft = KEY_A;
        _keyBomb = KEY_C;
    } else if (_plNb == 1) {
        _keyUp = KEY_UP;
        _keyDown = KEY_DOWN;
        _keyRight = KEY_RIGHT;
        _keyLeft = KEY_LEFT;
        _keyBomb = KEY_SPACE;
    } else if (_plNb == 2) {
        _keyUp = KEY_I;
        _keyDown = KEY_K;
        _keyRight = KEY_L;
        _keyLeft = KEY_J;
        _keyBomb = KEY_P;
    } else if (_plNb == 3) {
        _keyUp = KEY_T;
        _keyDown = KEY_V;
        _keyRight = KEY_G;
        _keyLeft = KEY_F;
        _keyBomb = KEY_N;
    }
}

bool Player::getExplosion()
{
    if (_bomb_explosion) {
        _bomb_explosion = false;
        return (true);
    }
    return (false);
}

void Player::keyPressedOnce()
{
    if (IsKeyPressed(_keyRight)) {
        _model->SetFrameCount(0);
    } else if (IsKeyPressed(_keyDown)) {
        _model->SetFrameCount(0);
    } else if (IsKeyPressed(_keyUp)) {
        _model->SetFrameCount(0);
    } else if (IsKeyPressed(_keyLeft)) {
        _model->SetFrameCount(0);
    }
    if (IsKeyPressed(_keyBomb)) {
        if (!_bombPlaced || (_powerUpBomb && _bombCpt < 2) && !_isDeadAlready) {
            _bombCpt += 1;
            _instanceGame.createBomb(round(_position.x), round(_position.z), "b");
            _bombPlaced = true;
            _startPlc = std::chrono::steady_clock::now();
            _bomb_explosion = true;
        }
    }
}

void Player::keyPressed(bool isColliding)
{
    if (IsKeyDown(_keyRight)) {
        if (!isColliding)
            _position.x += _speed;
        _model->Animation("runRight");
    } else if (IsKeyDown(_keyLeft)) {
        if (!isColliding)
            _position.x -= _speed;
        _model->Animation("runLeft");
    } else if (IsKeyDown(_keyUp)) {
        if (!isColliding)
            _position.z -= _speed;
        _model->Animation("runBack");
    } else if (IsKeyDown(_keyDown)) {
        if (!isColliding)
            _position.z += _speed;
        _model->Animation("runForward");
    } else {
        _model->Animation("idle");
    }
}

void Player::PollEvent(bool isColliding)
{
    keyPressedOnce();
    keyPressed(isColliding);
}

float Player::GetSpeedX()
{
    if (IsKeyDown(_keyRight))
        return _speed;
    else if (IsKeyDown(_keyLeft))
        return -_speed;
    return 0.0f;
}

float Player::GetSpeedZ()
{
    if (IsKeyDown(_keyUp)) {
        return -_speed;
    }
    else if (IsKeyDown(_keyDown))
        return _speed;
    return 0.0f;
}

std::string Player::GetName() const
{
    return _name;
}

void Player::SetName(std::string name)
{
    _name = name;
}

bool Player::GetIsPlaying()
{
    return _isPlaying;
}

void Player::SetIsPlaying(bool state)
{
    _isPlaying = state;
}

bool Player::GetHealth()
{
    return _isDead;
}

bool Player::GetDeath()
{
    return _isDeadAlready;
}

void Player::SetDeath(bool state)
{
    _isDeadAlready = state;
}

void Player::SetHealth(bool state)
{
    _isDead = state;
}

bool Player::GetSpeedEffect()
{
    return _powerUpSpeed;
}
bool Player::GetWallEffect()
{
    return _powerUpWall;
}
bool Player::GetFireEffect()
{
    return _powerUpFire;
}
bool Player::GetBombsEffect()
{
    return _powerUpBomb;
}
/*EFFECT MANAGER*/

float Player::timeLauncher(bool effect, std::chrono::_V2::steady_clock::time_point end,
                           std::chrono::_V2::steady_clock::time_point start)
{
    std::chrono::duration<double> elapsed_seconds;

    if (effect) {
        end = std::chrono::steady_clock::now();
        elapsed_seconds = end - start;
        return elapsed_seconds.count();
    }
    return -1;
}

void Player::timeManager()
{
    float ret = 0;
    if ((ret = timeLauncher(_powerUpSpeed, _endS, _startS)) != -1) {
        _elapsedTimeSpeed += ret;
        _startS = std::chrono::steady_clock::now();
    }
    if ((ret = timeLauncher(_powerUpWall, _endW, _startW)) != -1) {
        _elapsedTimeWall += ret;
        _startW = std::chrono::steady_clock::now();
    }
    if ((ret = timeLauncher(_powerUpFire, _endF, _startF)) != -1) {
        _elapsedTimeFire += ret;
        _startF = std::chrono::steady_clock::now();
    }
    if ((ret = timeLauncher(_powerUpBomb, _endB, _startB)) != -1) {
        _elapsedTimeBomb += ret;
        _startB = std::chrono::steady_clock::now();
    }
    if ((ret = timeLauncher(_bombPlaced, _endPlc, _startPlc)) != -1) {
        _elapsedTimePlc += ret;
        _startPlc = std::chrono::steady_clock::now();
    }
}

void Player::resetPlayer()
{
    _powerUpBomb = false;
    _powerUpWall = false;
    _powerUpFire = false;
    _powerUpSpeed = false;
    health = true;
    _isDead = false;
    _isDeadAlready = false;
}

void Player::manageChronoPlacedBomb()
{
    if (_bombPlaced) {
        if (_elapsedTimePlc > _effectDurationPlc) {
            _bombPlaced = false;
            _elapsedTimePlc = 0.0f;
            if (_powerUpBomb && _bombCpt > 1) {
                _bombCpt -= 2;
            } else {
                _bombCpt -= 1;
            }
        }
    }
}

void Player::manageChronoSpeed()
{
    if (_powerUpSpeed) {
        if (_elapsedTimeSpeed > _effectDurationSpeed) {
            _speed = 0.1;
            _powerUpSpeed = false;
            _elapsedTimeSpeed = 0.0f;
        }
    }
}

void Player::manageChronoWall()
{
    if (_powerUpWall) {
        if (_elapsedTimeWall > _effectDurationWall) {
            _powerUpWall = false;
            _elapsedTimeWall = 0.0f;
        }
    }
}

void Player::manageChronoFire()
{
    if (_powerUpFire) {
        if (_elapsedTimeFire > _effectDurationFire) {
            _powerUpFire = false;
            _elapsedTimeFire = 0.0f;
        }
    }
}

void Player::manageChronoBomb()
{
    if (_powerUpBomb) {
        if (_elapsedTimeBomb > _effectDurationBomb) {
            _powerUpBomb = false;
            _elapsedTimeBomb = 0.0f;
        }
    }
}

void Player::popBonus(Bonus target)
{
    for (auto it = _instanceGame._bonus.begin(); it != _instanceGame._bonus.end();) {
        if (it->GetPosition().x == target.GetPosition().x
            && it->GetPosition().y == target.GetPosition().y
            && it->GetPosition().z == target.GetPosition().z) {
            it = _instanceGame._bonus.erase(it);
        } else
            ++it;
    }
}

void Player::manageBonus(Bonus target)
{
    Bonus::OBJ type = target.GetBonusType();

    popBonus(target);
    if (type == Bonus::SPEED) {//pendant x sec
        _startS = std::chrono::steady_clock::now();
        _speed = 0.15;
        _powerUpSpeed = true;
    } else if (type == Bonus::WALL) {//pendant x sec
        _startW = std::chrono::steady_clock::now();
        _powerUpWall = true;
    } else if (type == Bonus::BOMB) {
        //std::cout << "---EFFECT BOMB" << std::endl;
        _startB = std::chrono::steady_clock::now();
        _powerUpBomb = true;
    } else if (type == Bonus::FIRE) {
        _startF = std::chrono::steady_clock::now();
        _powerUpFire = true;
    }
}
void Player::manageBonus(Effect target) { (void)target; }
void Player::manageBonus(Objects target) { (void)target; }
void Player::manageBonus(Wall target) { (void)target; }
void Player::manageBonus(Block target) { (void)target; }
/*!EFFECT MANAGER*/

bool Player::CollisionHandling()
{
    if (collisionManager(_instanceGame.getBonus(), GetSpeedX(), GetSpeedZ())) {
        return false;
    }
    if (collisionManager(_instanceGame.getEffects(), GetSpeedX(), GetSpeedZ())) {
        _isDead = true;
        return false;
    }
    if (!_powerUpWall) {
        if (collisionManager(_instanceGame.getBlock(), GetSpeedX(), GetSpeedZ()))
            return true;
    }
    if (collisionManager(_instanceGame.getWall(), GetSpeedX(), GetSpeedZ()))
        return true;
    return false;
}

AnimatedModel *Player::GetModel() const
{
    return (_model.get());
}

bool Player::getIsHuman() const
{
    return _isHuman;
}

void Player::setIsHuman(bool isHuman)
{
    _isHuman = isHuman;
}