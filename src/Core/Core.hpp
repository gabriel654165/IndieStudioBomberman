/*
** EPITECH PROJECT, 2021
** Indie studio
** File description:
** Core
*/

#ifndef CORE_H
#define CORE_H

#include <cstddef>
#include "../Lib/ITransform.hpp"
#include "../Lib/Scene/Window.hpp"
#include "../Utils/Timer.hpp"
#include "../GameManager/Game.hpp"
#include "../Lib/Scene/Cam.hpp"
#include "../Lib/Map/Movable/IA.hpp"

#include "../Lib/IU/NonSelectable/ShapeRect.hpp"
#include "../Lib/IU/NonSelectable/Text.hpp"
#include "../Lib/IU/Selectable/Button.hpp"
#include "../Lib/IU/Selectable/InputBox.hpp"
#include "../Lib/IU/NonSelectable/ShapeCircle.hpp"
#include "../Audio/Audio.hpp"
#include <memory>

#include "MenuOpt.h"
#include "CoreGameIU.hpp"
#include "CoreMenu.hpp"

class Core {
public:
    Core();
    ~Core() = default;

    void operator()();
    /*SET GAME*/
    void setTimer();
    void timeManager();
    void setGameDuration(float time);
    void SetBgMainMenu();
    void setCamera(int CameraMode);
    void resetCamera(int cameraMode);
    void eventManager();
    void setMusicsAndSounds();
    /*PLAYER*/
    void checkPlayersDeath();
    void drawPlayer();
    /*DRAW*/
    void draw3DComponents();
    void drawIUComponents();
    void DrawBgMainMenu();
    void drawMap();
    float getGameDuration() const;
    void manageAudio();
private:
    //in game variables
    Window _window;
    Cam _camera;
    Timer *_timer;
    float _elapsedTime;
    float _gameDuration;
    STATE _gameState;
    Audio _audio;
    Color _backGroundColor;
    //map
    Game _game;
    int _mapSizeWidth;
    int _mapSizeHeight;

    CoreGameIU _gameIU;
    CoreMenu _menuIU;
    std::vector<std::shared_ptr<Player>> _player;
    std::vector<std::shared_ptr<IA>> _ia;
    int _mapX;
    int _mapY;

    int _nb_player;
    int _nb_ia;
    //cine
    bool _introEnd;
    bool _introEndZoom;
    bool _restartAnim;
};


#endif //CORE_H
