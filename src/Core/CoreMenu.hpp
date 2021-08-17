/*
** EPITECH PROJECT, 2021
** Indie studio
** File description:
** CoreMenu
*/

#ifndef CORE_MENU_H
#define CORE_MENU_H

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
#include <map>
#include "MenuOpt.h"

class CoreMenu {
public:
    CoreMenu(Audio &_audio, Game &game, Cam &camera, STATE &gameState,
             int &mapX, int &mapY, Timer *&timer, float &elapsedTime,
             float &gameDuration, Window &window,
             std::vector<std::shared_ptr<Player>> &player,
             std::vector<std::shared_ptr<IA>> &ia,
             int &nb_player, int &nb_ia, Color &backGroundColor);
    ~CoreMenu() = default;

    void skinChoice4Left();
    void skinChoice4Right();
    void skinChoice3Left();
    void skinChoice3Right();
    void skinChoice2Left();
    void skinChoice2Right();
    void skinChoice1Left();
    void skinChoice1Right();
    void SetIUMainMenu();
    void setMenuOptions();
    void setMenuPlChoose();
    void setMenuPopUp();
    void setMainMenu();
    void setMenuCommands();
    void DrawIUMenu();
    int GetsaveNbIa();
    void SetsaveNbIa(int nbIa);
    int GetsaveNbPlayers();
    void SetsaveNbPLlayers(int nbPlayers);
    void resetDisplayPlayers();

    void addDuration();
    void dimDuration();
    void addVolume();
    void dimVolume();
    void addFps();
    void dimFps();
    void addSizeMap();
    void subSizeMap();
    void launchGame();
    void voidButton();
    void TwoPlayer();
    void ThreePlayer();
    void FourPlayer();
    void findPlayerPositions();
    void createPlayers();
    void setControlsPlayers();

    void goUp();
    void goDown();
    void goLeft();
    void goRigth();
    void goBomb();

    void setCamera(int cameraMode);
    void setMap();
    void setTimer();
    bool checkCameraPos();
    void timeManager();
    void drawMap();

    void IaChoose1();
    void IaChoose2();
    void IaChoose3();
    void IaChoose4();
    void PlChoose1();
    void PlChoose2();
    void PlChoose3();
    void PlChoose4();

    void setNightMode();
    void setDayMode();
    void setBlueMode();
    void setPurpleMode();
    void setBeigeMode();
    void setBrownMode();
    void setGreenMode();
    void setPinkMode();
    void setSkyMode();

    void setMenuState(MENU_STATE state);
    MENU_STATE GetMenuState();
    void setZoomIncr(float zoomincr);
private:
    MENU_STATE _menu_state;
    Audio &_audio;
    Game &_game;
    Cam &_camera;
    STATE &_gameState;
    Timer *&_timer;
    float &_elapsedTime;
    float &_gameDuration;
    std::vector<std::shared_ptr<Player>> &_player;
    std::vector<std::shared_ptr<IA>> &_ia;
    std::vector<std::shared_ptr<AnimatedModel>> _modelTab1;
    std::vector<std::shared_ptr<AnimatedModel>> _modelTab2;
    std::vector<std::shared_ptr<AnimatedModel>> _modelTab3;
    std::vector<std::shared_ptr<AnimatedModel>> _modelTab4;
    int &_nb_player;
    int &_nb_ia;

    Window &_window;
    Color &_backGroundColor;
    Font _font;
    int _saveNbPlayers;
    int _saveNbIa;
    float _zoomIncr;

    //menu button
    std::vector<Button> _mainMenuB;
    std::vector<Button> _startGameMenuB;
    std::vector<Button> _optionMenuB;
    std::vector<Button> _commandMenuB;
    //menu rect
    std::vector<ShapeRect> _mainMenuR;
    std::vector<int> _skinTab;
    std::vector<ShapeRect> _startGameMenuR;
    std::vector<ShapeRect> _optionMenuR;
    std::vector<ShapeRect> _commandMenuR;
    //menu text
    std::vector<Text> _mainMenuT;
    std::vector<Text> _startGameMenuT;
    std::vector<Text> _optionMenuT;
    std::vector<Text> _commandMenuT;
    // menu inputBox
    std::vector<InputBox> _startGameMenuI;
    std::vector<InputBox> _optionMenuI;

    bool _ia1 = false;
    bool _ia2 = false;
    bool _ia3 = false;
    bool _ia4 = false;

    bool _pl1 = true;
    bool _pl2 = true;
    bool _pl3 = true;
    bool _pl4 = true;

    int _mapX;
    int _mapY;
    float _elapsedTimeZoom;
    float _zoomDuration;
    std::chrono::_V2::steady_clock::time_point _start;
    std::chrono::_V2::steady_clock::time_point _end;
};


#endif //CORE_H
