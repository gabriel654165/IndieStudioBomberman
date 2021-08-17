/*
** EPITECH PROJECT, 2021
** Indie studio
** File description:
** CoreGameIU
*/

#ifndef CORE_GAME_IU_H
#define CORE_GAME_IU_H


#include "../Lib/ITransform.hpp"
#include "../Lib/Scene/Window.hpp"
#include "../Utils/Timer.hpp"
#include "../GameManager/Game.hpp"
#include "../Lib/Scene/Cam.hpp"
#include "../Lib/Map/Movable/Player.hpp"
#include "../Lib/Map/Movable/IA.hpp"

#include "../Lib/IU/NonSelectable/ShapeRect.hpp"
#include "../Lib/IU/NonSelectable/Text.hpp"
#include "../Lib/IU/Selectable/Button.hpp"
#include "../Lib/IU/Selectable/InputBox.hpp"
#include "../Lib/IU/NonSelectable/ShapeCircle.hpp"
#include "../Audio/Audio.hpp"
#include "../Lib/Map/Movable/Player.hpp"
#include "../Lib/IU/NonSelectable/Texture2D.hpp"

#include "MenuOpt.h"

#include <vector>
#include <tuple>
#include <chrono>

class CoreGameIU {
public:
    ~CoreGameIU() = default;
    CoreGameIU(bool &introEndZoom, bool &introEnd, Game &game, Cam &camera,
               Timer *&timer, bool &restartAnim, std::vector<std::shared_ptr<Player>> &player,
               std::vector<std::shared_ptr<IA>> &ia, int &nb_pl, int &nb_ia, float &gameDuration);

    void SetIUGame();
    void DrawIUGame(float time);
    void addScoreDeath();
    void setPlayerInfo();
    void updatePlayerInfo();
    const void drawPlayerInfo();
    void setTime(float time);
    void setMapSize(int mapX, int mapY);
    std::string setAvatarPL(int i);
    std::string setAvatarIA(int i);
    /*CINEMATICS*/
    float timeManager();
    void restartAnim();
    void introZoom();
    void introCount();
    bool checkCameraPos();
    void setMapIU();
    void drawMapIU();
    /*GAME OVER*/
    void setWinnerName();
    void DrawGameOver();
    /*EFFECTS*/
    Color SetBonusColor1(int i);
    Color SetBonusColor2(int i);
    Color SetBonusColor3(int i);
    Color SetBonusColor4(int i);
private:
    void setPlayerOneInfo();
    void setPlayerTwoInfo();
    void setPlayerThreeInfo();
    void setPlayerFourInfo();
    void getAllPlayers();
    std::vector<Button> _buttons;
    std::vector<Text> _texts;
    std::vector<Text> _introTexts;
    std::vector<Text> _restartText;
    std::vector<Text> _gameOverText;
    std::vector<ShapeRect> _gameOverRect;
    std::vector<ShapeRect> _rects;
    std::vector<std::tuple<ShapeCircle, Text>> _powerUps;
    std::vector<std::tuple<std::shared_ptr<Texture2d>, Text, ShapeCircle, ShapeCircle, ShapeCircle, ShapeCircle, Text, ShapeRect, Text>> _playerInfos;

    Text _scoreTxt;
    Text _winnerTxt;

    Font _font;
    
    int _score;
    float _time_num;
    float &_gameDuration;

    Text _time;
    Text _chooseSize;
    void drawMap();
    Cam &_camera;
    Game &_game;
    Timer *&_timer;
    std::vector<std::shared_ptr<Player>> &_player;
    std::vector<std::shared_ptr<IA>> &_ia;
    std::vector<std::shared_ptr<Player>> _players;
    bool _playersSet;
    int &_nb_player;
    int &_nb_ia;
    /*CINEMATICS*/
    bool &_introEnd;
    bool &_introEndZoom;
    float _elapsedTimeZoom;
    float _zoomDuration;
    float _elapsedTimeCount;
    float _countDuration;
    bool &_restartAnim;
    float _elapsedTimeRestart;
    std::chrono::_V2::steady_clock::time_point _start;
    std::chrono::_V2::steady_clock::time_point _end;
};


#endif //!CORE_GAME_IU_H
