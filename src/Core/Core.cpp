/*
** EPITECH PROJECT, 2021
** Indie studio
** File description:
** Core
*/

#include "Core.hpp"
#include <iostream>
#include <algorithm>

Core::Core() : _menuIU(_audio, _game, _camera, _gameState, _mapX, _mapY, _timer, _elapsedTime, _gameDuration, _window, _player, _ia, _nb_player, _nb_ia, _backGroundColor),
      _gameIU(_introEndZoom, _introEnd, _game, _camera, _timer, _restartAnim, _player, _ia, _nb_player, _nb_ia, _gameDuration)
{
    _window(1920, 1080);
    _gameDuration = 200.0f;
    _gameState = MENU;
    _timer = nullptr;
    _mapX = 15;
    _mapY = 15;
    _nb_player = 4;
    _nb_ia = 0;
    _introEnd = false;
    _introEndZoom = false;
    _restartAnim = false;
    _backGroundColor = BLACK;
}

void Core::setGameDuration(float time)
{
    _gameDuration = time;
}

void Core::setTimer()
{
    _timer = Timer::Instance();
    _elapsedTime = 0.0f;
}

void Core::timeManager()
{
    static int frames;
    _timer->Tick();
    _timer->Reset();
    _elapsedTime += _timer->DeltaTime();
    ++frames;
    if (_elapsedTime >= _gameDuration) {
        _gameState = GAMEOVER;
        _elapsedTime = 0.0f;
        frames = 0;
    }
}

void Core::eventManager()
{
    if (IsKeyPressed(KEY_ESCAPE)) {
        _audio.playSound(CLICK2);
        _audio.stopMusic(INGAME);
        _audio.setMusicLoop(START_MENU, true);
        _camera.setCameraMode(CAMERA_ORBITAL);
        _gameState = MENU;
        _menuIU.setMenuState(MAIN);
        _menuIU.setZoomIncr(100.0f);
        _menuIU.resetDisplayPlayers();
        SetBgMainMenu();
        _introEnd = false;
        _introEndZoom = false;
        _audio.playMusic(START_MENU);
    }
    if (IsKeyPressed(KEY_R)) {
        _restartAnim = true;
        resetCamera(CAMERA_CUSTOM);
        _gameState = GAME;
        _timer->Reset();
        _elapsedTime = 0.0f;
        _game.clearMap();
        _game.generateMap("");
        _nb_player = _menuIU.GetsaveNbPlayers();
        _nb_ia = _menuIU.GetsaveNbIa();
        for (auto &n: _player)
            n->resetPlayer();
        for (auto &it : _ia)
            it->resetPlayer();
        for (int i = 0; i < _menuIU.GetsaveNbPlayers(); ++i)
            _player.at(i)->SetIsPlaying(true);
        _menuIU.findPlayerPositions();
    }
}

void Core::setMusicsAndSounds()
{
    _audio.addMusic(START_MENU, "Assets/Sounds/super-bomberman-r-01-theme-song.mp3");
    _audio.addMusic(INGAME, "Assets/Sounds/main-theme-super-smash-bros-brawl.mp3");
    _audio.setVolume(0.5);
    _audio.setMusicLoop(START_MENU, true);
    _audio.addSound(CLICK1, "Assets/Sounds/mixkit-select-click-1109.wav");
    _audio.addSound(CLICK2, "Assets/Sounds/mixkit-click-error-1110.wav");
    _audio.addSound(CLICK3, "Assets/Sounds/mixkit-quick-win-video-game-notification-269.wav");

    _audio.addSound(EXPLOSION, "Assets/Sounds/explosion.mp3");
    _audio.addSound(BOMB, "Assets/Sounds/bomb.wav");

    _audio.playMusic(START_MENU);
}

void Core::resetCamera(int cameraMode)
{
    float value;
    _camera.setCameraMode(cameraMode);
    if (_game.getMapSize().first > _game.getMapSize().second)
        value = (float)(_game.getMapSize().first + 5);
    else
        value = (float)(_game.getMapSize().second + 13);
    _camera.setPosition(0.0f, value, 10.0f);
}

void Core::setCamera(int cameraMode)
{
    float value;
    _camera.setCameraMode(cameraMode);
    if (_game.getMapSize().first > _game.getMapSize().second)
        value = (float)(_game.getMapSize().first + 5);
    else
        value = (float)(_game.getMapSize().second + 13);
    _camera.setPosition(10.0f, 20.0f, 10.0f);
}

void Core::drawMap()
{
    for (auto &n: _game._wall)
        n.drawBlock();
    for (auto &n: _game._block)
        n.drawBlock();
    for (auto &n: _game._ground)
        n.drawBlock();
    for (auto &n: _game._bombs)
        n.drawBlock();
    for (auto &n: _game._effects)
        n.drawAnim();
    for (auto &n: _game._bonus) {
         n.draw();
    }
}

void Core::DrawBgMainMenu()
{
    for (int i = 0; i < _game._wall.size(); ++i)
        _game._wall[i].drawBlock();
    for (int i = 0; i < _game._block.size(); ++i)
        _game._block[i].drawBlock();
    for (int i = 0; i < _game._ground.size(); ++i)
        _game._ground[i].drawBlock();
}

void Core::SetBgMainMenu()
{
    _game.setMapSize(9, 9);
    _game.generateMap("menuMap.txt");
}

void Core::checkPlayersDeath()
{
    int i1 = 0;
    for (auto it = _ia.begin(); it != _ia.end() && i1 < _nb_ia; ++i1) {
        if (it->get()->GetHealth() && it->get()->GetIsPlaying() && !it->get()->GetDeath()) {
            it->get()->SetHealth(false);
            it->get()->SetDeath(true);
            std::cout << "\t[" << it->get()->GetName() << "]IS DEAD!!!!!" << std::endl;
            _nb_ia -= 1;
            _gameIU.addScoreDeath();
        } else
            ++it;
    }
    int i2 = 0;
    for (auto it = _player.begin(); it != _player.end() && i2 < _nb_player; ++i2) {
        if (it->get()->GetHealth() && it->get()->GetIsPlaying() && !it->get()->GetDeath()) {
            it->get()->SetHealth(false);
            it->get()->SetDeath(true);
            std::cout << "\t[" << it->get()->GetName() << "]IS DEAD!!!!!" << std::endl;
            _gameIU.addScoreDeath();
            _nb_player -= 1;
        } else
            ++it;
    }
    if (_nb_player + _nb_ia <= 1) {
        _gameIU.setWinnerName();
        _gameState = GAMEOVER;
    }
}

void Core::draw3DComponents()
{
    static int first = 0;

    _game.updateMap();
    BeginMode3D(_camera.getCamera());
    if (_gameState == MENU) {
        if (_menuIU.GetMenuState() != CHOOSE)
            DrawBgMainMenu();
    } else if (_gameState == GAME) {
        if (!_introEndZoom)
            _gameIU.introZoom();
        checkPlayersDeath();
        drawPlayer();
        drawMap();
    } else if (_gameState == GAMEOVER) {
        drawPlayer();
        drawMap();
    }
    EndMode3D();
}

void Core::manageAudio()
{
    for (auto &n: _player)
        if (n.get()->getExplosion())
            _audio.playSound(BOMB);
    for (auto &n: _ia)
        if (n.get()->getExplosion())
            _audio.playSound(BOMB);
}

void Core::drawIUComponents()
{
    BeginDrawing();
    if (_gameState == MENU) {
        _menuIU.DrawIUMenu();
    } else if (_gameState == GAME) {
        manageAudio();
        _gameIU.DrawIUGame(_elapsedTime);
        if (!_introEnd && _introEndZoom) {
            _gameIU.introCount();
        } else if (_restartAnim) {
            _gameIU.restartAnim();
        } else if (_introEndZoom && !_restartAnim) {
            timeManager();
            eventManager();
        }
    }
    if (_gameState == GAMEOVER) {
        _gameIU.DrawGameOver();
        eventManager();
    }
    EndDrawing();
}

void Core::drawPlayer()
{
    for (auto &it : _player) {
        if (_introEnd && _introEndZoom)
            if (it->GetIsPlaying())
                it->PollEvent(it->CollisionHandling());
        it->draw();
    }
    for (auto &it : _ia) {
        if (_introEnd && _introEndZoom)
            it->MovementManager(_player, _ia);
        it->draw();
    }
}

void Core::operator()()
{
    SetBgMainMenu();
    setCamera(CAMERA_ORBITAL);
    _menuIU.SetIUMainMenu();
    _gameIU.SetIUGame();
    setMusicsAndSounds();
    SetExitKey(KEY_F12);
    while (!WindowShouldClose()) {
        _audio.updateMusic();
        _camera.updateCamera();
        ClearBackground(_backGroundColor);
        if (_gameState == EXIT)
            break;
        draw3DComponents();
        drawIUComponents();
        //DrawFPS(10, 25);
    }
    Timer::Release();
}