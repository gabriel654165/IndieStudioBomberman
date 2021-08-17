//
// Created by gabi on 6/18/21.
//

#include "CoreGameIU.hpp"

CoreGameIU::CoreGameIU(bool &introEndZoom, bool &introEnd, Game &game, Cam &camera, Timer *&timer, bool &restartAnim, std::vector<std::shared_ptr<Player>> &player, std::vector<std::shared_ptr<IA>> &ia, int &nb_pl, int &nb_ia, float &gameDuration)
    : _introEndZoom(introEndZoom), _introEnd(introEnd), _game(game), _camera(camera), _timer(timer), _restartAnim(restartAnim), _player(player), _ia(ia), _nb_player(nb_pl), _nb_ia(nb_ia), _gameDuration(gameDuration)
{
    _introEnd = false;
    _introEndZoom = false;
    _elapsedTimeZoom = 0.0f;
    _zoomDuration = 0.5f;
    _elapsedTimeCount = 0.0f;
    _restartAnim = false;
    _elapsedTimeRestart = 0.0f;
    _font = LoadFont("Assets/Font/Retro_Gaming.ttf");
    _score = 1000;
}

void CoreGameIU::addScoreDeath()
{
    _score += 100;
}

void CoreGameIU::setWinnerName()
{
    std::string winnerName;

    for (auto &n: _player) {
        if (!n->GetDeath() && n->GetIsPlaying()) {
            winnerName = n->GetName();
            break;
        }
    }
    _winnerTxt.setText("Winner: " + winnerName);
}

void CoreGameIU::DrawGameOver()
{
    for (auto &n: _gameOverRect)
        n.draw();
    _scoreTxt.setText(std::to_string(_score));
    _scoreTxt.draw();
    _winnerTxt.draw();
    for (auto &n: _gameOverText)
        n.draw();
}
void CoreGameIU::SetIUGame()
{
    std::string timeStr("0.0");
    Text time((Vector2) {935, 60}, timeStr, 22, _font,  RED, false);
    _time = time;

    setMapIU();
    ShapeRect timeSqr((Vector2) {800, 40}, (Vector2) {320, 50}, Fade(GRAY, 0.5f));
    Text timerTxt((Vector2) {930, 40}, "TIME", 20, _font, WHITE, false);

    Text Three((Vector2) {(1920/2) + 100, (1080/2) + 250}, "3", 500, GetFontDefault(), RED, true);
    Text Two((Vector2) {(1920/2) + 100, (1080/2) + 250}, "2", 500, GetFontDefault(), ORANGE, true);
    Text One((Vector2) {(1920/2) + 40, (1080/2) + 250}, "1", 500, GetFontDefault(), GREEN, true);
    Text Go((Vector2) {(1920/2) + 320, (1080/2) + 250}, "GO", 500, GetFontDefault(), GREEN, true);

    Text RestartTxt((Vector2) {(1920/2)-50, (1080/2) - 400}, "Restart", 1, GetFontDefault(), RED, true);
    Text GameTxt((Vector2) {(1920/2)-40, (1080/2) + 400}, "Game", 1, GetFontDefault(), GREEN, true);

    ShapeRect gameOverSqr((Vector2) {0, 0}, (Vector2) {1920, 1080}, Fade(BLACK, 0.7f));
    Text gameOverTxt((Vector2) {820, 220}, "Game Finished !", 35, _font, RED, false);
    Text restart((Vector2) {900, 320}, "restart [R]", 20, _font, WHITE, false);
    Text exit((Vector2) {900, 350}, "quit [F12]", 20, _font, WHITE, false);
    Text back((Vector2) {840, 380}, "back to menu [escp]", 20, _font, WHITE, false);
    Text scoreOverTxt((Vector2) {925, 580}, "Score", 25, _font, RED, false);
    Text scoreTxt((Vector2) {940, 630}, "0 lol", 25, _font, GREEN, false);
    Text WinnerTxt((Vector2) {880, 180}, "Winner: ", 20, _font, GREEN, false);
    _scoreTxt = scoreTxt;
    _winnerTxt = WinnerTxt;
    _gameOverRect.push_back(gameOverSqr);
    _gameOverText.push_back(gameOverTxt);
    _gameOverText.push_back(restart);
    _gameOverText.push_back(exit);
    _gameOverText.push_back(back);
    _gameOverText.push_back(scoreOverTxt);

    _restartText.push_back(RestartTxt);
    _restartText.push_back(GameTxt);
    _introTexts.push_back(Three);
    _introTexts.push_back(Two);
    _introTexts.push_back(One);
    _introTexts.push_back(Go);
    _texts.push_back(timerTxt);

    _rects.push_back(timeSqr);
}

float CoreGameIU::timeManager()
{
    std::chrono::duration<double> elapsed_seconds;

    _end = std::chrono::steady_clock::now();
    elapsed_seconds = _end - _start;
    _start = std::chrono::steady_clock::now();
    return elapsed_seconds.count();
}

void CoreGameIU::restartAnim()
{
    _elapsedTimeRestart += timeManager();
    for (auto &n: _restartText) {
        n.setFontSize(n.getFontSize() + 1, true);
        n.draw();
    }
    if (_elapsedTimeRestart > 2.5f) {
        _restartAnim = false;
        _restartText.at(0).setPosition((1920/2)-50, (1080/2)-400, _restartText.at(0).GetPosition().z);
        _restartText.at(1).setPosition((1920/2)-40, (1080/2)+400, _restartText.at(1).GetPosition().z);
        _elapsedTimeRestart = 0.0f;
        for (auto &n: _restartText)
            n.setFontSize(1.0f);
    }
}

void CoreGameIU::DrawIUGame(float time)
{
    for (auto &n: _rects)
        n.draw();
    for (auto &n: _buttons)
        n.draw();
    for (auto &n: _texts)
        n.draw();
    _score = 1000 - (((1000 / _gameDuration) * _time_num));
    if (_score < 0)
        _score = 0;
    setMapSize(_game.getMapSize().first, _game.getMapSize().second);
    setTime(time);
    drawPlayerInfo();
    updatePlayerInfo();
    drawMapIU();
}

void CoreGameIU::setMapSize(int mapX, int mapY)
{
    std::string conversion = "< " + std::to_string(mapX) + "x" + std::to_string(mapY) + " >";
    _chooseSize.setText(conversion);
    _chooseSize.draw();
}

void CoreGameIU::setTime(float time)
{
    std::string timeStr(std::to_string(time));
    int size = timeStr.size();
    timeStr.erase(size - 5, 6);

    _time.setText(timeStr);
    _time.draw();
    _time_num = time;
}

std::string CoreGameIU::setAvatarPL(int i)
{
    std::string path;

    path = "Assets/model/" + _player.at(i)->GetModel()->GetName() + ".png";

    return path;
}

std::string CoreGameIU::setAvatarIA(int i)
{
    std::string path;

    path = "Assets/model/" + _ia.at(i)->GetModel()->GetName() + ".png";

    return path;
}

Color CoreGameIU::SetBonusColor1(int i)
{
    if (_players.at(i)->GetWallEffect())
        return GREEN;
    return Fade(GREEN, 0.1);
}

Color CoreGameIU::SetBonusColor2(int i)
{
    if (_players.at(i)->GetBombsEffect())
        return RED;
    return Fade(RED, 0.1);
}

Color CoreGameIU::SetBonusColor3(int i)
{
    if (_players.at(i)->GetFireEffect())
        return ORANGE;
    return Fade(ORANGE, 0.1);
}

Color CoreGameIU::SetBonusColor4(int i)
{
    if (_players.at(i)->GetSpeedEffect())
        return BLUE;
    return Fade(BLUE, 0.1);
}

const void CoreGameIU::drawPlayerInfo()//crash ici
{
    int i = 0;

    if (!_playersSet) {
        _playersSet = true;
        getAllPlayers();
        setPlayerInfo();
    }
    for (auto &it : _playerInfos) {
        std::get<0>(it)->draw();
        std::get<1>(it).draw();
        std::get<2>(it).setColor(SetBonusColor1(i));
        std::get<2>(it).draw();
        std::get<3>(it).setColor(SetBonusColor2(i));
        std::get<3>(it).draw();
        std::get<4>(it).setColor(SetBonusColor3(i));
        std::get<4>(it).draw();
        std::get<5>(it).setColor(SetBonusColor4(i));
        std::get<5>(it).draw();
        std::get<6>(it).setColor((!_players.at(i)->GetHealth()) ? GREEN : RED);
        std::get<6>(it).draw();
        std::get<7>(it).draw();
        if (_players.at(i)->GetDeath())
            std::get<8>(it).setText("0");
        else
            std::get<8>(it).setText(std::to_string(_score));
        std::get<8>(it).draw();
        i++;
    }
}

void CoreGameIU::setPlayerInfo()
{
    setPlayerOneInfo();
    setPlayerTwoInfo();
    if (_players.size() >= 3)
        setPlayerThreeInfo();
    if (_players.size() == 4)
        setPlayerFourInfo();
}

void CoreGameIU::setPlayerOneInfo()
{
    Vector2 size_text = MeasureTextEx(_font, "1000", 25, 25/10);
    _playerInfos.emplace_back(std::make_tuple(std::make_shared<Texture2d>("Assets/model/" + _players.at(0)->GetModel()->GetName() + ".png", (Vector2) {20, 220}, 0.2),
                                              Text((Vector2) {65, 305}, (_players.at(0)->getIsHuman()) ? "Player 1:" : "AI 1:", 25, _font, WHITE, true),
                                              ShapeCircle((Vector2) {145, 305}, 10, Fade(GREEN, 0.1)),
                                              ShapeCircle((Vector2) {165, 305}, 10, Fade(RED, 0.1)),
                                              ShapeCircle((Vector2) {185, 305}, 10, Fade(ORANGE, 0.1)),
                                              ShapeCircle((Vector2) {205, 305}, 10, Fade(BLUE, 0.1)),
                                              Text((Vector2) {85, 325}, "Name: " + _players.at(0)->GetName(), 25, _font, GREEN, true),
                                              ShapeRect((Vector2) {40, 340}, (Vector2) {size_text.x + 20, size_text.y + 10}, Fade(GREEN, 0.4f)),
                                              Text((Vector2) {40 + size_text.x/2 + 10, 340 + size_text.y/2 + 5}, "1000", 25, _font, WHITE, true))
    );
}

void CoreGameIU::setPlayerTwoInfo()
{
    Vector2 size_text = MeasureTextEx(_font, "1000", 25, 25/10);
    _playerInfos.emplace_back(
            std::make_tuple(std::make_unique<Texture2d>("Assets/model/" + _players.at(1)->GetModel()->GetName() + ".png", (Vector2) {20, 375}, 0.2),
                            Text((Vector2) {65, 460}, (_players.at(1)->getIsHuman()) ? "Player 2:" : "AI 2:", 25, _font, WHITE, true),
                            ShapeCircle((Vector2) {145, 460}, 10, Fade(GREEN, 0.1)),
                            ShapeCircle((Vector2) {165, 460}, 10, Fade(RED, 0.1)),
                            ShapeCircle((Vector2) {185, 460}, 10, Fade(ORANGE, 0.1)),
                            ShapeCircle((Vector2) {205, 460}, 10, Fade(BLUE, 0.1)),
                            Text((Vector2) {85, 480}, "Name: " + _players.at(1)->GetName(), 25, _font, GREEN, true),
                            ShapeRect((Vector2) {40, 495}, (Vector2) {size_text.x + 20, size_text.y + 10}, Fade(GREEN, 0.4f)),
                            Text((Vector2) {40 + size_text.x/2 + 10, 495 + size_text.y/2 + 5}, "1000", 25, _font, WHITE, true))
    );
}

void CoreGameIU::setPlayerThreeInfo()
{
    Vector2 size_text = MeasureTextEx(_font, "1000", 25, 25/10);
    _playerInfos.emplace_back(
            std::make_tuple(std::make_unique<Texture2d>("Assets/model/" + _players.at(2)->GetModel()->GetName() + ".png", (Vector2) {20, 530}, 0.2),
                            Text((Vector2) {65, 620}, (_players.at(2)->getIsHuman()) ? "Player 3:" : "AI 3:", 25, _font, WHITE, true),
                            ShapeCircle((Vector2) {145, 620}, 10, Fade(GREEN, 0.1)),
                            ShapeCircle((Vector2) {165, 620}, 10, Fade(RED, 0.1)),
                            ShapeCircle((Vector2) {185, 620}, 10, Fade(ORANGE, 0.1)),
                            ShapeCircle((Vector2) {205, 620}, 10, Fade(BLUE, 0.1)),
                            Text((Vector2) {85, 640}, "Name: " + _players.at(2)->GetName(), 25, _font, GREEN, true),
                            ShapeRect((Vector2) {40, 655}, (Vector2) {size_text.x + 20, size_text.y + 10}, Fade(GREEN, 0.4f)),
                            Text((Vector2) {40 + size_text.x/2 + 10, 655 + size_text.y/2 + 5}, "1000", 25, _font, WHITE, true))
    );
}

void CoreGameIU::setPlayerFourInfo()
{
    Vector2 size_text = MeasureTextEx(_font, "1000", 25, 25/10);
    _playerInfos.emplace_back(
            std::make_tuple(std::make_unique<Texture2d>("Assets/model/" + _players.at(3)->GetModel()->GetName() + ".png", (Vector2) {20, 690}, 0.2),
                            Text((Vector2) {65, 775}, (_players.at(3)->getIsHuman()) ? "Player 4:" : "AI 4:", 25, "Assets/Font/Retro_Gaming.ttf", WHITE, true),
                            ShapeCircle((Vector2) {145, 775}, 10, Fade(GREEN, 0.1)),
                            ShapeCircle((Vector2) {165, 775}, 10, Fade(RED, 0.1)),
                            ShapeCircle((Vector2) {185, 775}, 10, Fade(ORANGE, 0.1)),
                            ShapeCircle((Vector2) {205, 775}, 10, Fade(BLUE, 0.1)),
                            Text((Vector2) {85, 795}, "Name: " + _players.at(3)->GetName(), 25, _font, GREEN, true),
                            ShapeRect((Vector2) {40, 810}, (Vector2) {size_text.x + 20, size_text.y + 10}, Fade(GREEN, 0.4f)),
                            Text((Vector2) {40 + size_text.x/2 + 10, 810 + size_text.y/2 + 5}, "1000", 25, _font, WHITE, true))
    );
}

bool CoreGameIU::checkCameraPos()
{
    float value;

    if (_game.getMapSize().first > _game.getMapSize().second)//jsuqu'a cette size
        value = (float)(_game.getMapSize().first + 5);
    else
        value = (float)(_game.getMapSize().second + 13);

    if (_camera.GetPosition().y <= value) {
        return true;
    }
    return false;
}

void CoreGameIU::introZoom()
{
    static float incr = 100.0f;

    _elapsedTimeZoom += timeManager();
    if (_elapsedTimeZoom >= _zoomDuration)
        incr -= 0.5f;
    _camera.setPosition(0.0f, incr, 20.0f);
    _camera.updateCamera();
    drawMap();
    if (checkCameraPos()) {
        _introEndZoom = true;
        incr = 100.0f;
    }
}

void CoreGameIU::introCount()
{
    static bool threeB = false;
    static bool secB = false;
    static bool oneB = false;
    static float sizeText = 50;

    for (auto &n: _introTexts)
    n.setFontSize(sizeText, true);
    _elapsedTimeCount += timeManager();
    if (_elapsedTimeCount > 1.0f) {
        sizeText = 50.0f;
    } else
        sizeText += 0.5f;

    if (!oneB && secB && threeB) {
        if (_elapsedTimeCount > 1.0f) {
            _elapsedTimeCount = 0.0f;
            oneB = true;
        }
        _introTexts.at(2).draw();
    } else if (threeB && !secB && !oneB) {
        if (_elapsedTimeCount > 1.0f) {
            _elapsedTimeCount = 0.0f;
            secB = true;
        }
        _introTexts.at(1).draw();
    } else if (!secB && !oneB && !threeB) {
        if (_elapsedTimeCount > 1.0f) {
            threeB = true;
            _elapsedTimeCount = 0.0f;
        }
        _introTexts.at(0).draw();
    } else if (oneB && secB && threeB) {
        _introTexts.at(3).draw();
        if (_elapsedTimeCount > 1.0f) {
            _timer->Reset();
            _introEnd = true;
            threeB = false;
            secB = false;
            oneB = false;
            sizeText = 50.0f;
        }
    }
}

void CoreGameIU::drawMap()
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

void CoreGameIU::updatePlayerInfo()
{
    int i = 0;

    for (auto &it : _player) {
        if (it->GetBombsEffect())
            std::get<4>(_playerInfos.at(i)).setColor(ORANGE);
        else
            std::get<4>(_playerInfos.at(i)).setColor(Fade(ORANGE, 0.1));
        if (it->GetFireEffect())
            std::get<3>(_playerInfos.at(i)).setColor(RED);
        else
            std::get<3>(_playerInfos.at(i)).setColor(Fade(RED, 0.1));
        if (it->GetSpeedEffect())
            std::get<5>(_playerInfos.at(i)).setColor(BLUE);
        else
            std::get<5>(_playerInfos.at(i)).setColor(Fade(BLUE, 0.1));
        if (it->GetWallEffect())
            std::get<2>(_playerInfos.at(i)).setColor(GREEN);
        else
            std::get<2>(_playerInfos.at(i)).setColor(Fade(GREEN, 0.1));
    }
}

void CoreGameIU::setMapIU()
{
    _powerUps.emplace_back(std::make_tuple(ShapeCircle((Vector2) {1650, 320}, 20, GREEN),
                                           Text((Vector2) {1800, 320}, "WALL PASS!", 30, _font, WHITE, true)));
    _powerUps.emplace_back(std::make_tuple(ShapeCircle((Vector2) {1650, 320 + 135}, 20, RED),
                                           Text((Vector2) {1800, 320 + 135}, "BOMB UP!", 30, _font, WHITE, true)));
    _powerUps.emplace_back(std::make_tuple(ShapeCircle((Vector2) {1650, 320 + 270}, 20, ORANGE),
                                           Text((Vector2) {1800, 320 + 270}, "FIRE UP!", 30, _font, WHITE, true)));
    _powerUps.emplace_back(std::make_tuple(ShapeCircle((Vector2) {1650, 320 + 270 + 135}, 20, BLUE),
                                           Text((Vector2) {1800, 320 + 270 + 135}, "SPEED UP!", 30, _font, WHITE, true)));
}

void CoreGameIU::drawMapIU()
{
    for (auto &it : _powerUps) {
        std::get<0>(it).draw();
        std::get<1>(it).draw();
    }
}

void CoreGameIU::getAllPlayers()
{
    for (auto &it : _player) {
        _players.emplace_back(it);
    }
    for (auto &it : _ia) {
        _players.emplace_back(it);
    }
}