/*
** EPITECH PROJECT, 2021
** Indie studio
** File description:
** Core
*/

#include "CoreMenu.hpp"

CoreMenu::CoreMenu(Audio &audio, Game &game, Cam &camera, STATE &gameState, int &mapX, int &mapY, Timer *&timer, float &elapsedTime, float &gameDuration, Window &window, std::vector<std::shared_ptr<Player>> &players, std::vector<std::shared_ptr<IA>> &ia, int &nb_player, int &nb_ia, Color &backGroundColor)
        : _audio(audio), _game(game), _camera(camera), _gameState(gameState), _mapX(mapX), _mapY(mapY), _timer(timer), _elapsedTime(elapsedTime), _gameDuration(gameDuration), _window(window), _player(players), _ia(ia), _nb_player(nb_player), _nb_ia(nb_ia), _backGroundColor(backGroundColor)
{
    std::vector<std::string> nameTab = {"trump", "wiiFit", "mouse", "dora"};
    _modelTab1.emplace_back(std::make_shared<AnimatedModel>(nameTab.at(0)));
    _modelTab1.emplace_back(std::make_shared<AnimatedModel>(nameTab.at(1)));
    _modelTab1.emplace_back(std::make_shared<AnimatedModel>(nameTab.at(2)));
    _modelTab1.emplace_back(std::make_shared<AnimatedModel>(nameTab.at(3)));
    _modelTab2.emplace_back(std::make_shared<AnimatedModel>(nameTab.at(0)));
    _modelTab2.emplace_back(std::make_shared<AnimatedModel>(nameTab.at(1)));
    _modelTab2.emplace_back(std::make_shared<AnimatedModel>(nameTab.at(2)));
    _modelTab2.emplace_back(std::make_shared<AnimatedModel>(nameTab.at(3)));
    _modelTab3.emplace_back(std::make_shared<AnimatedModel>(nameTab.at(0)));
    _modelTab3.emplace_back(std::make_shared<AnimatedModel>(nameTab.at(1)));
    _modelTab3.emplace_back(std::make_shared<AnimatedModel>(nameTab.at(2)));
    _modelTab3.emplace_back(std::make_shared<AnimatedModel>(nameTab.at(3)));
    _modelTab4.emplace_back(std::make_shared<AnimatedModel>(nameTab.at(0)));
    _modelTab4.emplace_back(std::make_shared<AnimatedModel>(nameTab.at(1)));
    _modelTab4.emplace_back(std::make_shared<AnimatedModel>(nameTab.at(2)));
    _modelTab4.emplace_back(std::make_shared<AnimatedModel>(nameTab.at(3)));
    for (int i = 0; i < 4; i++)
        _skinTab.emplace_back(0);
    _mapX = 15;
    _mapY = 15;
    _menu_state = MAIN;
    _window.setFPS(60);
    _audio.setVolume(0.3f);
    _font = LoadFont("Assets/Font/Wash_Your_Hand.ttf");
    _elapsedTimeZoom = 0.0f;
    _zoomDuration = 1.0f;
    _nb_player = 4;
    _nb_ia = 0;
    _saveNbPlayers = 0;
    _saveNbIa = 0;
    _zoomIncr = 100.0f;
}

MENU_STATE CoreMenu::GetMenuState()
{
    return _menu_state;
}

void CoreMenu::setMenuState(MENU_STATE state)
{
    _menu_state = state;
}

int CoreMenu::GetsaveNbPlayers()
{
    return _saveNbPlayers;
}
void CoreMenu::SetsaveNbPLlayers(int nbPlayers)
{
    _saveNbPlayers = nbPlayers;
}

int CoreMenu::GetsaveNbIa()
{
    return _saveNbIa;
}
void CoreMenu::SetsaveNbIa(int nbIa)
{
    _saveNbIa = nbIa;
}

void CoreMenu::createPlayers()
{
    int j = 0;

    _player.erase(_player.begin(), _player.end());
    _ia.erase(_ia.begin(), _ia.end());

    for (int i = 0; i < _nb_player; ++i, ++j) {
        if (j == 0) {
            auto mod = std::make_shared<AnimatedModel>((std::string &) _modelTab1.at(_skinTab.at(j))->GetName());
            _player.emplace_back(std::make_shared<Player>(_game, (Vector3) {0, 0, 0}, mod));
        } else if (j == 1) {
            auto mod = std::make_shared<AnimatedModel>((std::string &) _modelTab2.at(_skinTab.at(j))->GetName());
            _player.emplace_back(std::make_shared<Player>(_game, (Vector3) {0, 0, 0}, mod));
        } else if (j == 2) {
            auto mod = std::make_shared<AnimatedModel>((std::string &) _modelTab3.at(_skinTab.at(j))->GetName());
            _player.emplace_back(std::make_shared<Player>(_game, (Vector3) {0, 0, 0}, mod));
        } else if (j == 3) {
            auto mod = std::make_shared<AnimatedModel>((std::string &) _modelTab4.at(_skinTab.at(j))->GetName());
            _player.emplace_back(std::make_shared<Player>(_game, (Vector3) {0, 0, 0}, mod));
        }
    }
    for (int i = 0; i < _nb_ia; ++i, ++j) {
        if (j == 0) {
            auto mod = std::make_shared<AnimatedModel>((std::string &) _modelTab1.at(_skinTab.at(j))->GetName());
            _ia.emplace_back(std::make_shared<IA>(_game, (Vector3) {0, 0, 0}, mod));
        } else if (j == 1) {
            auto mod = std::make_shared<AnimatedModel>((std::string &) _modelTab2.at(_skinTab.at(j))->GetName());
            _ia.emplace_back(std::make_shared<IA>(_game, (Vector3) {0, 0, 0}, mod));
        } else if (j == 2) {
            auto mod = std::make_shared<AnimatedModel>((std::string &) _modelTab3.at(_skinTab.at(j))->GetName());
            _ia.emplace_back(std::make_shared<IA>(_game, (Vector3) {0, 0, 0}, mod));
        } else if (j == 3) {
            auto mod = std::make_shared<AnimatedModel>((std::string &) _modelTab4.at(_skinTab.at(j))->GetName());
            _ia.emplace_back(std::make_shared<IA>(_game, (Vector3) {0, 0, 0}, mod));
        }
    }
}

void CoreMenu::setControlsPlayers()
{
    int i = 0;
    for (auto it = _player.begin(); it != _player.end(); ++it, ++i) {
        _player.at(i)->setNbControls(i);
    }
}

void CoreMenu::launchGame()
{
    _gameState = GAME;
    _audio.stopMusic(START_MENU);
    _audio.playSound(CLICK3);
    _audio.playMusic(INGAME);
    setTimer();
    setMap();
    _game.updateMap();
    _camera.setPosition(0.0f, _zoomIncr, 20.0f);
    _camera.setCameraMode(CAMERA_CUSTOM);
    createPlayers();
    setControlsPlayers();
    findPlayerPositions();
    _saveNbPlayers = _nb_player;
    _saveNbIa = _nb_ia;
    int j = 0;
    for (int i = 0; i < _nb_player; ++i, ++j)
        _player.at(i)->SetName(_startGameMenuI.at(j).GetText());
    for (int i = 0; i < _nb_ia; ++i, ++j)
        _ia.at(i)->SetName(_startGameMenuI.at(j).GetText());
}

void CoreMenu::findPlayerPositions()
{
    float genPos;
    genPos = (int)((_mapX / 2) - 1);
    std::vector<Vector3> posTab = {
            (Vector3){-genPos, -0.2f, -genPos},
            (Vector3){genPos, -0.2f, -genPos},
            (Vector3){-genPos, -0.2f, genPos},
            (Vector3){genPos, -0.2f, genPos}};

    auto ite = posTab.begin();
    for (auto &it : _player) {
        it->setPosition(ite->x, ite->y, ite->z);
        ite++;
    }
    for (auto &it : _ia) {
        it->setPosition(ite->x, ite->y, ite->z);
        ite++;
    }
}

void CoreMenu::setCamera(int cameraMode)
{
    float value;
    _camera.setCameraMode(cameraMode);
    if (_game.getMapSize().first > _game.getMapSize().second)//jsuqu'a cette size
        value = (float)(_game.getMapSize().first + 5);
    else
        value = (float)(_game.getMapSize().second + 13);
    _camera.setPosition(0.0f, value, 20.0f);
}

void CoreMenu::setZoomIncr(float zoomincr)
{
    _zoomIncr = zoomincr;
}

void CoreMenu::addVolume()
{
    float volume = _audio.getVolume();
    if (volume <= 1.0f) {
        _audio.setVolume(volume + 0.1f);
        _optionMenuT[0].setText("VOLUME : " + std::to_string((int)((volume + 0.1f) * 100.0f)));
    }
}

void CoreMenu::dimVolume()
{
    float volume = _audio.getVolume();
    if (volume >= 0.0f) {
        _audio.setVolume(volume - 0.1f);
        _optionMenuT[0].setText("VOLUME : " + std::to_string((int)((volume + 0.1f) * 100.0f)));
    }
}

void CoreMenu::addFps()
{
    int fps = _window.getFPS();

    if (fps < 120) {
        _window.setFPS(fps + 10);
        _optionMenuT[1].setText("FPS : " + std::to_string(fps + 10));
    }
}

void CoreMenu::dimFps()
{
    int fps = _window.getFPS();

    if (fps > 10) {
        _window.setFPS(fps - 10);
        _optionMenuT[1].setText("FPS : " + std::to_string(fps - 10));
    }
}

void CoreMenu::addSizeMap()
{
    _mapX += 2;
    _mapY += 2;
}

void CoreMenu::subSizeMap()
{
    if (!(_mapX < 10 || _mapY < 10)) {
        _mapX -= 2;
        _mapY -= 2;
    }
}

void CoreMenu::addDuration()
{
    _gameDuration += 60.0f; 
    std::string timeStr(std::to_string(_gameDuration));
    int size = timeStr.size();
    timeStr.erase(size - 7, 7);
    timeStr = timeStr + " Seconds";
    _startGameMenuT[4].setText(timeStr);
    
    
    
}

void CoreMenu::dimDuration()
{
    if (_gameDuration >= 120.0f) {
        _gameDuration -= 60.0f;
        std::string timeStr(std::to_string(_gameDuration));
        int size = timeStr.size();
        timeStr.erase(size - 7, 7);
        timeStr = timeStr + " Seconds";
        _startGameMenuT[4].setText(timeStr);
    }
}

void CoreMenu::goUp()
{
    if (_commandMenuT[0].getBoolDraw()) {
        _commandMenuT[0].setBoolDraw(false);
        _commandMenuT[1].setBoolDraw(false);
        _commandMenuT[2].setBoolDraw(false);
        _commandMenuT[3].setBoolDraw(false);
        _commandMenuT[4].setBoolDraw(false);
    } else {
        _commandMenuT[0].setBoolDraw(true);
        _commandMenuT[1].setBoolDraw(false);
        _commandMenuT[2].setBoolDraw(false);
        _commandMenuT[3].setBoolDraw(false);
        _commandMenuT[4].setBoolDraw(false);
    }
}

void CoreMenu::goDown()
{
    if (_commandMenuT[1].getBoolDraw()) {
        _commandMenuT[0].setBoolDraw(false);
        _commandMenuT[1].setBoolDraw(false);
        _commandMenuT[2].setBoolDraw(false);
        _commandMenuT[3].setBoolDraw(false);
        _commandMenuT[4].setBoolDraw(false);
    } else {
        _commandMenuT[0].setBoolDraw(false);
        _commandMenuT[1].setBoolDraw(true);
        _commandMenuT[2].setBoolDraw(false);
        _commandMenuT[3].setBoolDraw(false);
        _commandMenuT[4].setBoolDraw(false);
    }
}
void CoreMenu::goLeft()
{
    if (_commandMenuT[2].getBoolDraw()) {
        _commandMenuT[0].setBoolDraw(false);
        _commandMenuT[1].setBoolDraw(false);
        _commandMenuT[2].setBoolDraw(false);
        _commandMenuT[3].setBoolDraw(false);
        _commandMenuT[4].setBoolDraw(false);
    } else {
        _commandMenuT[0].setBoolDraw(false);
        _commandMenuT[1].setBoolDraw(false);
        _commandMenuT[2].setBoolDraw(true);
        _commandMenuT[3].setBoolDraw(false);
        _commandMenuT[4].setBoolDraw(false);
    }
}
void CoreMenu::goRigth()
{
    if (_commandMenuT[3].getBoolDraw()) {
        _commandMenuT[0].setBoolDraw(false);
        _commandMenuT[1].setBoolDraw(false);
        _commandMenuT[2].setBoolDraw(false);
        _commandMenuT[3].setBoolDraw(false);
        _commandMenuT[4].setBoolDraw(false);
    } else {
        _commandMenuT[0].setBoolDraw(false);
        _commandMenuT[1].setBoolDraw(false);
        _commandMenuT[2].setBoolDraw(false);
        _commandMenuT[3].setBoolDraw(true);
        _commandMenuT[4].setBoolDraw(false);
    }
}
void CoreMenu::goBomb()
{
    if (_commandMenuT[4].getBoolDraw()) {
        _commandMenuT[0].setBoolDraw(false);
        _commandMenuT[1].setBoolDraw(false);
        _commandMenuT[2].setBoolDraw(false);
        _commandMenuT[3].setBoolDraw(false);
        _commandMenuT[4].setBoolDraw(false);
    } else {
        _commandMenuT[0].setBoolDraw(false);
        _commandMenuT[1].setBoolDraw(false);
        _commandMenuT[2].setBoolDraw(false);
        _commandMenuT[3].setBoolDraw(false);
        _commandMenuT[4].setBoolDraw(true);
    }
}


void CoreMenu::voidButton()
{
}

void CoreMenu::setMenuOptions()
{
    _audio.playSound(CLICK1);
    _menu_state = OPTIONS;
}
void CoreMenu::setMenuCommands()
{
    _audio.playSound(CLICK1);
    _menu_state = COMMANDS;
}

void CoreMenu::skinChoice1Left()
{
    if (_skinTab.at(0) - 1 < 0) {
        _skinTab.at(0) = 3;
    } else
        _skinTab.at(0) -= 1;
    _modelTab1.at(_skinTab.at(0))->SetFrameCount(0);
    _camera.setPosition(0.0f, 0.0f, 0.0f);
    _camera.setCameraMode(CAMERA_CUSTOM);
    _camera.updateCamera();
    _audio.playSound(CLICK1);
    _menu_state = CHOOSE;
}
void CoreMenu::skinChoice1Right()
{
    if (_skinTab.at(0) + 1 > 3) {
        _skinTab.at(0) = 0;
    } else
        _skinTab.at(0) += 1;
    _modelTab1.at(_skinTab.at(0))->SetFrameCount(0);
    _camera.setPosition(0.0f, 0.0f, 0.0f);
    _camera.setCameraMode(CAMERA_CUSTOM);
    _camera.updateCamera();
    _audio.playSound(CLICK1);
    _menu_state = CHOOSE;
}
void CoreMenu::skinChoice2Left()
{
    if (_skinTab.at(1) - 1 < 0) {
        _skinTab.at(1) = 3;
    } else
        _skinTab.at(1) -= 1;
    _modelTab2.at(_skinTab.at(0))->SetFrameCount(0);
    _camera.setPosition(0.0f, 0.0f, 0.0f);
    _camera.setCameraMode(CAMERA_CUSTOM);
    _camera.updateCamera();
    _audio.playSound(CLICK1);
    _menu_state = CHOOSE;
}
void CoreMenu::skinChoice2Right()
{
    _modelTab2.at(_skinTab.at(0))->SetFrameCount(0);
    if (_skinTab.at(1) + 1 > 3) {
        _skinTab.at(1) = 0;
    } else
        _skinTab.at(1) += 1;
    _camera.setPosition(0.0f, 0.0f, 0.0f);
    _camera.setCameraMode(CAMERA_CUSTOM);
    _camera.updateCamera();
    _audio.playSound(CLICK1);
    _menu_state = CHOOSE;
}
void CoreMenu::skinChoice3Left()
{
    if (_skinTab.at(2) - 1 < 0) {
        _skinTab.at(2) = 3;
    } else
        _skinTab.at(2) -= 1;
    _modelTab3.at(_skinTab.at(0))->SetFrameCount(0);
    _camera.setPosition(0.0f, 0.0f, 0.0f);
    _camera.setCameraMode(CAMERA_CUSTOM);
    _camera.updateCamera();
    _audio.playSound(CLICK1);
    _menu_state = CHOOSE;
}
void CoreMenu::skinChoice3Right()
{
    if (_skinTab.at(2) + 1 > 3) {
        _skinTab.at(2) = 0;
    } else
        _skinTab.at(2) += 1;
    _modelTab3.at(_skinTab.at(0))->SetFrameCount(0);
    _camera.setPosition(0.0f, 0.0f, 0.0f);
    _camera.setCameraMode(CAMERA_CUSTOM);
    _camera.updateCamera();
    _audio.playSound(CLICK1);
    _menu_state = CHOOSE;
}
void CoreMenu::skinChoice4Left()
{
    if (_skinTab.at(3) - 1 < 0) {
        _skinTab.at(3) = 3;
    } else
        _skinTab.at(3) -= 1;
    _modelTab4.at(_skinTab.at(0))->SetFrameCount(0);
    _camera.setPosition(0.0f, 0.0f, 0.0f);
    _camera.setCameraMode(CAMERA_CUSTOM);
    _camera.updateCamera();
    _audio.playSound(CLICK1);
    _menu_state = CHOOSE;
}
void CoreMenu::skinChoice4Right()
{
    if (_skinTab.at(3) + 1 > 3) {
        _skinTab.at(3) = 0;
    } else
        _skinTab.at(3) += 1;
    _modelTab4.at(_skinTab.at(0))->SetFrameCount(0);
    _camera.setPosition(0.0f, 0.0f, 0.0f);
    _camera.setCameraMode(CAMERA_CUSTOM);
    _camera.updateCamera();
    _audio.playSound(CLICK1);
    _menu_state = CHOOSE;
}

void CoreMenu::setMenuPlChoose()
{
    _camera.setPosition(0.0f, 0.0f, 0.0f);
    _camera.setCameraMode(CAMERA_CUSTOM);
    _camera.updateCamera();
    _audio.playSound(CLICK1);
    _menu_state = CHOOSE;
}
void CoreMenu::setMenuPopUp()
{
    _audio.playSound(CLICK1);
    _gameState = EXIT;
}
void CoreMenu::setMainMenu()
{
    _camera.setPosition(10.0f, 20.0f, 10.0f);
    _camera.setCameraMode(CAMERA_ORBITAL);
    _camera.updateCamera();
    _audio.playSound(CLICK2);
    _menu_state = MAIN;
}

void CoreMenu::DrawIUMenu()
{
    static std::vector<Vector3> posVector = {(Vector3){-0.7, 0.35, 5}, (Vector3){1.1, 0.35, 5}, (Vector3){-0.7, -1.6, 5}, (Vector3){1.1, -1.6, 5}};
    if (_menu_state == MAIN) {
        for (int i = 0; i < _mainMenuB.size(); i++) {
            _mainMenuB[i].draw();
        }
        for (int j = 0; j < _mainMenuR.size(); j++) {
            _mainMenuR[j].draw();
        }
        for (int k = 0; k < _mainMenuT.size(); k++) {
            _mainMenuT[k].draw();
        }
    }
    if (_menu_state == OPTIONS) {
        for (int j = 0; j < _optionMenuR.size(); j++) {
            _optionMenuR[j].draw();
        }
        for (int i = 0; i < _optionMenuB.size(); i++) {
            _optionMenuB[i].draw();
        }
        for (int k = 0; k < _optionMenuT.size(); k++) {
            _optionMenuT[k].draw();
        }
    }
    if (_menu_state == COMMANDS) {
        for (int j = 0; j < _commandMenuR.size(); j++) {
            _commandMenuR[j].draw();
        }
        for (int i = 0; i < _commandMenuB.size(); i++) {
            _commandMenuB[i].draw();
        }
        for (int k = 0; k < _commandMenuT.size(); k++) {
            _commandMenuT[k].draw();
        }
    }
    if (_menu_state == CHOOSE) {
        for (int j = 0; j < (_nb_player + _nb_ia); j++) {
            BeginMode3D(_camera.getCamera());
            _camera.setPosition(0, 0, 10);
            if (j == 0) {
                _modelTab1.at(_skinTab.at(j))->Animation("dance");
                DrawModelEx(_modelTab1.at(_skinTab.at(j))->GetModel(), posVector.at(j),
                    (Vector3) {-1.0f, 0.0f, 0.0f}, 90.0f, _modelTab1.at(_skinTab.at(j))->GetIuModelScale(),
                    WHITE);
            } else if (j == 1) {
                _modelTab2.at(_skinTab.at(j))->Animation("dance");
                DrawModelEx(_modelTab2.at(_skinTab.at(j))->GetModel(), posVector.at(j),
                    (Vector3) {-1.0f, 0.0f, 0.0f}, 90.0f, _modelTab2.at(_skinTab.at(j))->GetIuModelScale(),
                    WHITE);
            } else if (j == 2) {
                _modelTab3.at(_skinTab.at(j))->Animation("dance");
                DrawModelEx(_modelTab3.at(_skinTab.at(j))->GetModel(), posVector.at(j),
                    (Vector3) {-1.0f, 0.0f, 0.0f}, 90.0f, _modelTab3.at(_skinTab.at(j))->GetIuModelScale(),
                    WHITE);
            } else if (j == 3) {
                _modelTab4.at(_skinTab.at(j))->Animation("dance");
                DrawModelEx(_modelTab4.at(_skinTab.at(j))->GetModel(), posVector.at(j),
                    (Vector3) {-1.0f, 0.0f, 0.0f}, 90.0f, _modelTab4.at(_skinTab.at(j))->GetIuModelScale(),
                    WHITE);
            }
            _camera.updateCamera();
            EndMode3D();
        }
        for (int i = 0; i < (18 + ((_nb_player + _nb_ia) * 4))/*_startGameMenuB.size()*/; i++) {
            _startGameMenuB[i].draw();
        }
        _startGameMenuT.at(2).setText(std::to_string(_mapX) + "X" + std::to_string(_mapY));//belek seg
        for (int k = 0; k < _startGameMenuT.size(); k++) {
            _startGameMenuT[k].draw();
        }
        for (int l = 0; l < (_nb_player + _nb_ia) /*_startGameMenuI.size()*/; l++) {
            _startGameMenuI[l].draw();
        }
    }
}

void CoreMenu::TwoPlayer()
{
    _nb_player = 2;
    _nb_ia = 0;
    _startGameMenuI.at(0).SetText("Player 1");
    _startGameMenuI.at(1).SetText("Player 2");
    _startGameMenuT[0].setText("PLAYER NUMBER : 2");
}

void CoreMenu::ThreePlayer()
{
    _nb_player = 3;
    _nb_ia = 0;
    _startGameMenuI.at(0).SetText("Player 1");
    _startGameMenuI.at(1).SetText("Player 2");
    _startGameMenuI.at(2).SetText("Player 3");
    _startGameMenuT[0].setText("PLAYER NUMBER : 3");
}
void CoreMenu::FourPlayer()
{
    _nb_player = 4;
    _nb_ia = 0;
    _startGameMenuI.at(0).SetText("Player 1");
    _startGameMenuI.at(1).SetText("Player 2");
    _startGameMenuI.at(2).SetText("Player 3");
    _startGameMenuI.at(2).SetText("Player 4");
    _startGameMenuT[0].setText("PLAYER NUMBER : 4");
}

void CoreMenu::resetDisplayPlayers()
{
    _nb_player = 4;
    _nb_ia = 0;
    _startGameMenuI.at(0).SetText("Player 1");
    _startGameMenuI.at(1).SetText("Player 2");
    _startGameMenuI.at(2).SetText("Player 3");
    _startGameMenuI.at(3).SetText("Player 4");
    _ia1 = false;
    _ia2 = false;
    _ia3 = false;
    _ia4 = false;
    _pl1 = true;
    _pl2 = true;
    _pl3 = true;
    _pl4 = true;
}

void CoreMenu::IaChoose1()
{
    if (!_ia1 && (_nb_player - 1) != 0) {
        _startGameMenuI.at(0).SetText("IA 1");
        _ia1 = true;
        _pl1 = false;
        _nb_ia += 1;
        _nb_player -= 1;
    }
}

void CoreMenu::IaChoose2()
{
    if (!_ia2 && (_nb_player - 1) != 0) {
        _startGameMenuI.at(1).SetText("IA 2");
        _ia2 = true;
        _pl2 = false;
        _nb_ia += 1;
        _nb_player -= 1;
    }
}

void CoreMenu::IaChoose3()
{
    if (!_ia3 && (_nb_player - 1) != 0) {
        _startGameMenuI.at(2).SetText("IA 3");
        _ia3 = true;
        _pl3 = false;
        _nb_ia += 1;
        _nb_player -= 1;
    }
}
void CoreMenu::IaChoose4()
{
    if (!_ia4 && (_nb_player - 1) != 0) {
        _startGameMenuI.at(3).SetText("IA 4");
        _ia4 = true;
        _pl4 = false;
        _nb_ia += 1;
        _nb_player -= 1;
    }
}

void CoreMenu::PlChoose1()
{
    if (!_pl1) {
        _startGameMenuI.at(0).SetText("Player 1");
        _pl1 = true;
        _ia1 = false;
        _nb_ia -= 1;
        _nb_player += 1;
    }
}
void CoreMenu::PlChoose2()
{
    if (!_pl2) {
        _startGameMenuI.at(1).SetText("Player 2");
        _pl2 = true;
        _ia2 = false;
        _nb_ia -= 1;
        _nb_player += 1;
    }
}
void CoreMenu::PlChoose3()
{
    if (!_pl3) {
        _startGameMenuI.at(2).SetText("Player 3");
        _pl3 = true;
        _ia3 = false;
        _nb_ia -= 1;
        _nb_player += 1;
    }
}
void CoreMenu::PlChoose4()
{
    if (!_pl4) {
        _startGameMenuI.at(3).SetText("Player 4");
        _pl4 = true;
        _ia4 = false;
        _nb_ia -= 1;
        _nb_player += 1;
    }
}

void CoreMenu::setNightMode() {
    _backGroundColor = BLACK;
}
void CoreMenu::setDayMode() {
    _backGroundColor = LIGHTGRAY;
}
void CoreMenu::setBlueMode() {
    _backGroundColor = DARKBLUE;
}
void CoreMenu::setPurpleMode() {
    _backGroundColor = DARKPURPLE;
}
void CoreMenu::setBeigeMode() {
    _backGroundColor = BEIGE;
}
void CoreMenu::setBrownMode() {
    _backGroundColor = DARKBROWN;
}
void CoreMenu::setGreenMode() {
    _backGroundColor = DARKGREEN;
}
void CoreMenu::setPinkMode() {
    _backGroundColor = MAGENTA;
}

void CoreMenu::setSkyMode() {
    _backGroundColor = SKYBLUE;
}


void CoreMenu::SetIUMainMenu()
{
    /////////////////////////////////////////////////////////////MAIN

    Vector2 rect_size = {(1920/6), (1080/16)};
    Vector2 button1_pos = {(((1920/6)) - (rect_size.x/2)), ((1080/3) - (rect_size.y/2))};
    Vector2 button2_pos = {(((1920/6)) - (rect_size.x/2)), button1_pos.y + (rect_size.y)*2};
    Vector2 button3_pos = {(((1920/6)) - (rect_size.x/2)), button2_pos.y + (rect_size.y)*2};
    Vector2 button4_pos = {(((1920/6)) - (rect_size.x/2)), button3_pos.y + (rect_size.y)*2};

    ShapeRect rect((Vector2) {(((1920/6) * 5) - (rect_size.x/2)), (1080/8)}, (Vector2) {(1920/6), ((1080/8) * 6)}, Fade(GRAY, 0.5f));

    Button back("<BACK", (Vector2) {32, 1080/12}, rect_size,_font, 25, BLACK, WHITE, [this] { setMainMenu(); });

    Button start("START>", (Vector2) {1920-32 - rect_size.x, (1080/8) * 7}, rect_size,_font, 25, GREEN, WHITE, [this] { launchGame(); });

    Text tittle((Vector2) {1920/2, (1080/6)}, "BOMBER MAN", 60, "Assets/Font/bomberman.ttf", RED, true);

    Text high_score((Vector2) {((((1920/6) * 5) - (rect_size.x/2)) + (1920/12)), (1080/12) * 3}, "HIGH SCORE", 25,_font, WHITE, true);
    Text player1((Vector2) {((((1920/6) * 5) - (rect_size.x/2)) + (1920/12)), (1080/12) * 4}, "TOP 1", 25,_font, WHITE, true);
    Text p1_score((Vector2) {((((1920/6) * 5) - (rect_size.x/2)) + (1920/12)), (1080/12) * 5}, "1520", 25,_font, WHITE, true);
    Text player2((Vector2) {((((1920/6) * 5) - (rect_size.x/2)) + (1920/12)), (1080/12) * 6}, "TOP 2", 25,_font, WHITE, true);
    Text p2_score((Vector2) {((((1920/6) * 5) - (rect_size.x/2)) + (1920/12)), (1080/12) * 7}, "1000", 25,_font, WHITE, true);
    Text player3((Vector2) {((((1920/6) * 5) - (rect_size.x/2)) + (1920/12)), (1080/12) * 8}, "TOP 3", 25,_font, WHITE, true);
    Text p3_score((Vector2) {((((1920/6) * 5) - (rect_size.x/2)) + (1920/12)), (1080/12) * 9}, "530", 25,_font, WHITE, true);

    Button button1("Start Game", button1_pos, rect_size,_font, 25, GRAY, WHITE, [this] { setMenuPlChoose(); });
    Button button2("Options", button2_pos, rect_size, _font, 25, GRAY, WHITE, [this] { setMenuOptions(); });
    Button button3("Commands", button3_pos, rect_size, _font, 25, GRAY, WHITE, [this] { setMenuCommands(); });
    Button button4("Exit", button4_pos, rect_size, _font, 25, GRAY, WHITE, [this] { setMenuPopUp(); });

    _mainMenuT.push_back(high_score);
    _mainMenuT.push_back(player1);
    _mainMenuT.push_back(p1_score);
    _mainMenuT.push_back(player2);
    _mainMenuT.push_back(p2_score);
    _mainMenuT.push_back(player3);
    _mainMenuT.push_back(tittle);
    _mainMenuT.push_back(p3_score);

    _mainMenuT.push_back(tittle);
    _mainMenuB.push_back(button1);
    _mainMenuB.push_back(button2);
    _mainMenuB.push_back(button3);
    _mainMenuB.push_back(button4);
    _mainMenuR.push_back(rect);

    /////////////////////////////////////////////////////////////MAIN

    Text pl_nb((Vector2) {32 + (rect_size.x/2), 1080/6 + (rect_size.y/2)}, ("PLAYER NUMBER : 4"), 25,_font, WHITE, true);

    Button two_player("2", (Vector2) {32 + rect_size.x/4, ((1080/6) + 32 + (rect_size.y*1))}, (Vector2) {rect_size.x/2, rect_size.y/2}, _font, 40, GRAY, WHITE, [this] { TwoPlayer(); });
    Button three_player("3", (Vector2) {32 + rect_size.x/4, ((1080/6) + 32 + rect_size.y*2)}, (Vector2) {rect_size.x/2, rect_size.y/2}, _font, 40, GRAY, WHITE, [this] { ThreePlayer(); });
    Button four_player("4", (Vector2) {32 + rect_size.x/4, ((1080/6) + 32 + (rect_size.y*3))}, (Vector2) {rect_size.x/2, rect_size.y/2}, _font, 40, GRAY, WHITE, [this] { FourPlayer(); });

    Text map_size((Vector2) {32 + (rect_size.x/2), (1080/6) + 32 + (rect_size.y*4 + 32)}, "MAP SIZE", 25, _font, WHITE, true);
    Text map_size_value((Vector2) {32 + (rect_size.x/2), (1080/6) + 32 + (rect_size.y*4) + 60}, (std::to_string(_mapX) + "X" + std::to_string(_mapY)), 40, _font, WHITE, true);

    Button add_map_size("+", (Vector2) {32 + rect_size.x/4, (1080/6) + 32 + (rect_size.y*4) + 60 + rect_size.y}, (Vector2) {rect_size.x/2, rect_size.y/2}, _font, 50, GRAY, WHITE, [this] { addSizeMap(); });
    Button dim_map_size("-", (Vector2) {32 + rect_size.x/4, (1080/6) + 32 + (rect_size.y*4) + 60 + (rect_size.y * 2)}, (Vector2) {rect_size.x/2, rect_size.y/2}, _font, 50, GRAY, WHITE, [this] { subSizeMap(); });

    std::cout << (1080/6) + 32 + (rect_size.y*4) + 60 + (rect_size.y * 2) << std::endl;

    Text set_time((Vector2) {32 + (rect_size.x/2), 674 + (rect_size.y * 2)}, "GAME TIME", 25, _font, WHITE, true);
    std::string timeStr(std::to_string(_gameDuration));
    int size = timeStr.size();
    timeStr.erase(size - 7, 7);
    Text time_value((Vector2) {32 + (rect_size.x/2), 674 + 60 + (rect_size.y * 2)}, (timeStr + " Seconds"), 40, _font, WHITE, true);

    Button add_time("+", (Vector2) {32 + rect_size.x/4, (674 + 60 + rect_size.y) + (rect_size.y * 2)}, (Vector2) {rect_size.x/2, rect_size.y/2}, _font, 50, GRAY, WHITE, [this] { addDuration(); });
    Button dim_time("-", (Vector2) {32 + rect_size.x/4, (674 + 60 + (rect_size.y*2)) + (rect_size.y * 2)}, (Vector2) {rect_size.x/2, rect_size.y/2}, _font, 50, GRAY, WHITE, [this] { dimDuration(); });

    Font retro = LoadFont("Assets/Font/Retro_Gaming.ttf");
    InputBox input_name1((Vector2) {634, 30}, (Vector2) {(1920/6 - 40), (1080/16)}, retro, 40, 0, GRAY, WHITE, [this] {voidButton();});
    InputBox input_name2((Vector2) {1106, 30}, (Vector2) {(1920/6 - 40), (1080/16)}, retro, 40, 0, GRAY, WHITE, [this] {voidButton();});
    InputBox input_name3((Vector2) {634, 560}, (Vector2) {(1920/6 - 40), (1080/16)}, retro, 40, 0, GRAY, WHITE, [this] {voidButton();});
    InputBox input_name4((Vector2) {1106, 560}, (Vector2) {(1920/6 - 40), (1080/16)}, retro, 40, 0, GRAY, WHITE, [this] {voidButton();});

    Button p1("P", (Vector2) {704, 491}, (Vector2) {50, 50},_font, 25, GRAY, WHITE, [this] { PlChoose1(); });
    Button ia1("AI", (Vector2) {794, 491}, (Vector2) {50, 50},_font, 25, GRAY, WHITE, [this] { IaChoose1(); });

    Button p2("P", (Vector2) {1176, 491}, (Vector2) {50, 50},_font, 25, GRAY, WHITE, [this] { PlChoose2(); });
    Button ia2("AI", (Vector2) {1266, 491}, (Vector2) {50, 50},_font, 25, GRAY, WHITE, [this] { IaChoose2(); });

    Button p3("P", (Vector2) {704, 1021}, (Vector2) {50, 50},_font, 25, GRAY, WHITE, [this] { PlChoose3(); });
    Button ia3("AI", (Vector2) {794, 1021}, (Vector2) {50, 50},_font, 25, GRAY, WHITE, [this] { IaChoose3(); });

    Button p4("P", (Vector2) {1176, 1021}, (Vector2) {50, 50},_font, 25, GRAY, WHITE, [this] { PlChoose4(); });
    Button ia4("AI", (Vector2) {1266, 1021}, (Vector2) {50, 50},_font, 25, GRAY, WHITE, [this] { IaChoose4(); });

    ShapeRect rect_p1((Vector2) {684, 1080/5 - 105}, (Vector2) {(1920/6 - 140), (1080/3)}, Fade(GRAY, 0.5f));
    ShapeRect rect_p2((Vector2) {1156, 1080/5 - 105}, (Vector2) {(1920/6 - 140), (1080/3)}, Fade(GRAY, 0.5f));
    ShapeRect rect_p3((Vector2) {684, 687 - 36 - 10}, (Vector2) {(1920/6 - 140), (1080/3)}, Fade(GRAY, 0.5f));
    ShapeRect rect_p4((Vector2) {1156, 687 - 36 - 10}, (Vector2) {(1920/6 - 140), (1080/3)}, Fade(GRAY, 0.5f));

    Button player1_left("<", (Vector2) {634, (1080/3) - 105}, (Vector2) {40, 40}, "Assets/Font/Wash_Your_Hand.ttf", 40, GRAY, WHITE, [this] { skinChoice1Left(); });
    Button player1_right(">", (Vector2) {878, (1080/3) - 105}, (Vector2) {40, 40}, "Assets/Font/Wash_Your_Hand.ttf", 40, GRAY, WHITE, [this] { skinChoice1Right(); });
    Button player2_left("<", (Vector2) {1106, (1080/3) - 105}, (Vector2) {40, 40}, "Assets/Font/Wash_Your_Hand.ttf", 40, GRAY, WHITE, [this] { skinChoice2Left(); });
    Button player2_right(">", (Vector2) {1350, (1080/3) - 105}, (Vector2) {40, 40}, "Assets/Font/Wash_Your_Hand.ttf", 40, GRAY, WHITE, [this] { skinChoice2Right(); });
    Button player3_left("<", (Vector2) {634, 831 - 36 - 10}, (Vector2) {40, 40}, "Assets/Font/Wash_Your_Hand.ttf", 40, GRAY, WHITE, [this] { skinChoice3Left(); });
    Button player3_right(">", (Vector2) {878, 831 - 36 - 10}, (Vector2) {40, 40}, "Assets/Font/Wash_Your_Hand.ttf", 40, GRAY, WHITE, [this] { skinChoice3Right(); });
    Button player4_left("<", (Vector2) {1106, 831 - 36 - 10}, (Vector2) {40, 40}, "Assets/Font/Wash_Your_Hand.ttf", 40, GRAY, WHITE, [this] { skinChoice4Left(); });
    Button player4_right(">", (Vector2) {1350, 831 - 36 - 10}, (Vector2) {40, 40}, "Assets/Font/Wash_Your_Hand.ttf", 40, GRAY, WHITE, [this] { skinChoice4Right(); });

    Button nightMode("Dark mode", (Vector2) {1532 + rect_size.x/4, ((1080/4) + 32 + (rect_size.y*(-2)))}, (Vector2) {rect_size.x/2, rect_size.y/2}, _font, 20, DARKGRAY, WHITE, [this] { setNightMode(); });
    Button dayMode("Light mode", (Vector2) {1532 + rect_size.x/4, ((1080/4) + 32 + rect_size.y*(-1))}, (Vector2) {rect_size.x/2, rect_size.y/2}, _font, 20, GRAY, WHITE, [this] { setDayMode(); });
    Button blueMode("Blue mode", (Vector2) {1532 + rect_size.x/4, ((1080/4) + 32)}, (Vector2) {rect_size.x/2, rect_size.y/2}, _font, 20, BLUE, WHITE, [this] { setBlueMode(); });
    Button purpleMode("Purple mode", (Vector2) {1532 + rect_size.x/4, ((1080/4) + 32 + rect_size.y*5)}, (Vector2) {rect_size.x/2, rect_size.y/2}, _font, 20, PURPLE, WHITE, [this] { setPurpleMode(); });
    Button beigeMode("Beige mode", (Vector2) {1532 + rect_size.x/4, ((1080/4) + 32 + rect_size.y*1)}, (Vector2) {rect_size.x/2, rect_size.y/2}, _font, 20, BEIGE, WHITE, [this] { setBeigeMode(); });
    Button brownMode("Brown mode", (Vector2) {1532 + rect_size.x/4, ((1080/4) + 32 + rect_size.y*2)}, (Vector2) {rect_size.x/2, rect_size.y/2}, _font, 20, BROWN, WHITE, [this] { setBrownMode(); });
    Button greenMode("Green mode", (Vector2) {1532 + rect_size.x/4, ((1080/4) + 32 + rect_size.y*3)}, (Vector2) {rect_size.x/2, rect_size.y/2}, _font, 20, GREEN, WHITE, [this] { setGreenMode(); });
    Button pinkMode("Pink mode", (Vector2) {1532 + rect_size.x/4, ((1080/4) + 32 + rect_size.y*4)}, (Vector2) {rect_size.x/2, rect_size.y/2}, _font, 20, MAGENTA, WHITE, [this] { setPinkMode(); });
    Button skyMode("SKY mode", (Vector2) {1532 + rect_size.x/4, ((1080/4) + 32 + rect_size.y*5)}, (Vector2) {rect_size.x/2, rect_size.y/2}, _font, 20, SKYBLUE, WHITE, [this] { setSkyMode(); });
    
    

    // Button

    // 18 + (_nb_player * 4)
    _startGameMenuB.push_back(nightMode);
    _startGameMenuB.push_back(dayMode);
    _startGameMenuB.push_back(blueMode);
    _startGameMenuB.push_back(purpleMode);
    _startGameMenuB.push_back(beigeMode);
    _startGameMenuB.push_back(brownMode);
    _startGameMenuB.push_back(greenMode);
    _startGameMenuB.push_back(pinkMode);
    _startGameMenuB.push_back(skyMode);

    _startGameMenuB.push_back(add_time);
    _startGameMenuB.push_back(dim_time);

    _startGameMenuB.push_back(back);
    _startGameMenuB.push_back(start);

    _startGameMenuB.push_back(two_player);
    _startGameMenuB.push_back(three_player);
    _startGameMenuB.push_back(four_player);
    _startGameMenuB.push_back(add_map_size);
    _startGameMenuB.push_back(dim_map_size);

    _startGameMenuB.push_back(player1_left);
    _startGameMenuB.push_back(player1_right);
    _startGameMenuB.push_back(p1);
    _startGameMenuB.push_back(ia1);

    _startGameMenuB.push_back(player2_left);
    _startGameMenuB.push_back(player2_right);
    _startGameMenuB.push_back(p2);
    _startGameMenuB.push_back(ia2);

    _startGameMenuB.push_back(player3_left);
    _startGameMenuB.push_back(player3_right);
    _startGameMenuB.push_back(p3);
    _startGameMenuB.push_back(ia3);

    _startGameMenuB.push_back(player4_left);
    _startGameMenuB.push_back(player4_right);
    _startGameMenuB.push_back(p4);
    _startGameMenuB.push_back(ia4);

    //input box
    _startGameMenuI.push_back(input_name1);
    _startGameMenuI.push_back(input_name2);
    _startGameMenuI.push_back(input_name3);
    _startGameMenuI.push_back(input_name4);

    // rect
    _startGameMenuR.push_back(rect_p1);
    _startGameMenuR.push_back(rect_p2);
    _startGameMenuR.push_back(rect_p3);
    _startGameMenuR.push_back(rect_p4);

    // text
    _startGameMenuT.push_back(pl_nb);
    _startGameMenuT.push_back(map_size);
    _startGameMenuT.push_back(map_size_value);
    _startGameMenuT.push_back(set_time);
    _startGameMenuT.push_back(time_value);
    

    /////////////////////////////////////////////////////////////COMMAND

    Vector2 sqr = {60, 60};

    Button cmd_p1_u("Z", (Vector2) {587, 395}, sqr,_font, 50, Fade(BLUE, 0.5f), WHITE, [this] { goUp(); });
    Button cmd_p1_l("Q", (Vector2) {504, 478}, sqr,_font, 50, Fade(RED, 0.5f), WHITE, [this] { goLeft(); });
    Button cmd_p1_d("S", (Vector2) {587, 478}, sqr,_font, 50, Fade(YELLOW, 0.5f), WHITE, [this] { goDown(); });
    Button cmd_p1_r("D", (Vector2) {670, 478}, sqr,_font, 50, Fade(GREEN, 0.5f), WHITE, [this] { goRigth(); });
    Button cmd_p1_b("C", (Vector2) {711, 561}, sqr,_font, 50, Fade(GRAY, 0.5f), WHITE, [this] { goBomb(); });

    Button cmd_p2_u("^", (Vector2) {1227, 395}, sqr,_font, 50, Fade(BLUE, 0.5f), WHITE, [this] { goUp(); });
    Button cmd_p2_l("<", (Vector2) {1144, 478}, sqr,_font, 50, Fade(RED, 0.5f), WHITE, [this] { goLeft(); });
    Button cmd_p2_d("v", (Vector2) {1227, 478}, sqr,_font, 50, Fade(YELLOW, 0.5f), WHITE, [this] { goDown(); });
    Button cmd_p2_r(">", (Vector2) {1310, 478}, sqr,_font, 50, Fade(GREEN, 0.5f), WHITE, [this] { goRigth(); });
    Button cmd_p2_b("SP", (Vector2) {1351, 561}, sqr,_font, 50, Fade(GRAY, 0.5f), WHITE, [this] { goBomb(); });

    Button cmd_p3_u("I", (Vector2) {587, 755}, sqr,_font, 50, Fade(BLUE, 0.5f), WHITE, [this] { goUp(); });
    Button cmd_p3_l("J", (Vector2) {504, 838}, sqr,_font, 50, Fade(RED, 0.5f), WHITE, [this] { goLeft(); });
    Button cmd_p3_d("K", (Vector2) {587, 838}, sqr,_font, 50, Fade(YELLOW, 0.5f), WHITE, [this] { goDown(); });
    Button cmd_p3_r("L", (Vector2) {670, 838}, sqr,_font, 50, Fade(GREEN, 0.5f), WHITE, [this] { goRigth(); });
    Button cmd_p3_b("P", (Vector2) {711, 921}, sqr,_font, 50, Fade(GRAY, 0.5f), WHITE, [this] { goBomb(); });

    Button cmd_p4_u("T", (Vector2) {1227, 755}, sqr,_font, 60, Fade(BLUE, 0.5f), WHITE, [this] { goUp(); });
    Button cmd_p4_l("F", (Vector2) {1144, 838}, sqr,_font, 50, Fade(RED, 0.5f), WHITE, [this] { goLeft(); });
    Button cmd_p4_d("V", (Vector2) {1227, 838}, sqr,_font, 50, Fade(YELLOW, 0.5f), WHITE, [this] { goDown(); });
    Button cmd_p4_r("G", (Vector2) {1310, 838}, sqr,_font, 50, Fade(GREEN, 0.5f), WHITE, [this] { goRigth(); });
    Button cmd_p4_b("N", (Vector2) {1351, 921}, sqr,_font, 40, Fade(GRAY, 0.5f), WHITE, [this] { goBomb(); });

    ShapeRect rect_command1((Vector2) {0, 0}, (Vector2) {1920,  1080}, Fade(BLACK, 0.5f));

    Text tittle_command((Vector2) {1920/2, 1080/6}, "COMMANDS", 50, _font, WHITE, true);
    Text playerOne((Vector2) {1920/6 * 2, 1080/6 + 150}, "PLAYER 1", 40, _font, WHITE, true);
    Text playerTwo((Vector2) {1920/6 * 4, 1080/6 + 150}, "PLAYER 2", 40, _font, WHITE, true);
    Text playerThree((Vector2) {1920/6 * 2, 1080/2 + 150}, "PLAYER 3", 40, _font, WHITE, true);
    Text playerFour((Vector2) {1920/6 * 4, 1080/2 + 150}, "PLAYER 4", 40, _font, WHITE, true);
    
    Vector2 go_pos = {(1920/6) + (((1920/6) * 4)/2), ((1080/6) + 100) + ((1080/6 * 4)/2)};
    
    Text goUp(go_pos, "Go UP!", 40, _font, BLUE, true);
    Text goDown(go_pos, "Go DOWN!", 40, _font, YELLOW, true);
    Text goLeft(go_pos, "Go LEFT!", 40, _font, RED, true);
    Text goRight(go_pos, "Go RIGHT!", 40, _font, GREEN, true);
    Text goBomb(go_pos, "Drop BOMB!", 40, _font, BLACK, true);

    goUp.setBoolDraw(false);
    goDown.setBoolDraw(false);
    goLeft.setBoolDraw(false);
    goRight.setBoolDraw(false);
    goBomb.setBoolDraw(false);

    _commandMenuT.push_back(goUp);
    _commandMenuT.push_back(goDown);
    _commandMenuT.push_back(goLeft);
    _commandMenuT.push_back(goRight);
    _commandMenuT.push_back(goBomb);
    _commandMenuT.push_back(playerOne);
    _commandMenuT.push_back(playerTwo);
    _commandMenuT.push_back(playerThree);
    _commandMenuT.push_back(playerFour);
    _commandMenuT.push_back(tittle_command);

    _commandMenuR.push_back(rect_command1);

    _commandMenuB.push_back(cmd_p1_u);
    _commandMenuB.push_back(cmd_p1_l);
    _commandMenuB.push_back(cmd_p1_d);
    _commandMenuB.push_back(cmd_p1_r);
    _commandMenuB.push_back(cmd_p1_b);

    _commandMenuB.push_back(cmd_p2_u);
    _commandMenuB.push_back(cmd_p2_l);
    _commandMenuB.push_back(cmd_p2_d);
    _commandMenuB.push_back(cmd_p2_r);
    _commandMenuB.push_back(cmd_p2_b);

    _commandMenuB.push_back(cmd_p3_u);
    _commandMenuB.push_back(cmd_p3_l);
    _commandMenuB.push_back(cmd_p3_d);
    _commandMenuB.push_back(cmd_p3_r);
    _commandMenuB.push_back(cmd_p3_b);

    _commandMenuB.push_back(cmd_p4_u);
    _commandMenuB.push_back(cmd_p4_l);
    _commandMenuB.push_back(cmd_p4_d);
    _commandMenuB.push_back(cmd_p4_r);
    _commandMenuB.push_back(cmd_p4_b);

    _commandMenuB.push_back(back);

    /////////////////////////////////////////////////////////////OPTION

    ShapeRect rect_setting((Vector2) {0, 0}, (Vector2) {1920, 1080}, Fade(BLACK, 0.5f));

    Text volume_value((Vector2) {1920/4 + 160, 1080/4 + 1080/8}, "VOLUME : " + std::to_string((int)(_audio.getVolume() * 100.0f)), 25, _font, WHITE, true);
    Text fps_value((Vector2) {1920/4 + 160, 1080/2 + 1080/8}, "FPS : " + std::to_string(_window.getFPS()), 25, _font, WHITE, true);

    Button add_volume("+", (Vector2) {((1920/4) + (320 * 2) + 80), 1080/4 + 1080/8 - 33}, (Vector2) {rect_size.x/2, rect_size.y/2}, _font, 50, GRAY, WHITE, [this] { addVolume(); });
    Button dim_volume("-", (Vector2) {((1920/4) + 320 + 80), 1080/4 + 1080/8 - 33}, (Vector2) {rect_size.x/2, rect_size.y/2}, _font, 50, GRAY, WHITE, [this] { dimVolume(); });

    Button add_fps("+", (Vector2) {((1920/4) + (320 * 2) + 80), 1080/2 + 1080/8 - 33}, (Vector2) {rect_size.x/2, rect_size.y/2}, _font, 50, GRAY, WHITE, [this] { addFps(); });
    Button dim_fps("-", (Vector2) {((1920/4) + 320 + 80), 1080/2 + 1080/8 - 33}, (Vector2) {rect_size.x/2, rect_size.y/2}, _font, 50, GRAY, WHITE, [this] { dimFps(); });

    Text tittle_option((Vector2) {1920/2, (1080/6)}, "OPTIONS", 50, _font, WHITE, true);

    _optionMenuB.push_back(back);

    _optionMenuR.push_back(rect_setting);

    _optionMenuT.push_back(volume_value);
    _optionMenuT.push_back(fps_value);
    _optionMenuT.push_back(tittle_option);

    _optionMenuB.push_back(add_volume);
    _optionMenuB.push_back(dim_volume);
    _optionMenuB.push_back(add_fps);
    _optionMenuB.push_back(dim_fps);
}

void CoreMenu::setMap()
{
    _game.setMapSize(_mapX, _mapY);
    _game.generateMap("");
}

void CoreMenu::setTimer()
{
    _timer = Timer::Instance();
    _elapsedTime = 0.0f;
}
