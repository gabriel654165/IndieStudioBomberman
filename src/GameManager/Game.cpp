/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-gabriel.medoukali
** File description:
** Game
*/

#include "Game.hpp"

Game::Game()
{
    _wall_texture = LoadTexture("Assets/texture/wall.png");
    _wall_d_texture = LoadTexture("Assets/texture/wall_d.png");
    _Floor_texture = LoadTexture("Assets/texture/floor.png");
    std::srand(std::time(0));
    _mapX = 15;
    _mapY = 13;
}

Game::Game(int sizeX, int sizeY)
{
    std::srand(std::time(0));
    _mapX = sizeX;
    _mapY = sizeY;
}

Game::~Game()
{
}

void Game::parseLine(int z, std::string line)
{
    Block block;
    Wall wall;
    std::string symb;
    
    for (int x = 0; line[x]; x++) {
        symb = line[x];

        wall = createWall(x, z, symb);
        if ((wall.GetPosition().x) != -1000.0f)
            _wall.push_back(wall);

        block = createBlock(x, z, symb);
        if ((block.GetPosition().x) != -1000.0f)
            _block.push_back(block);

        wall = createGround(x, z);
        _ground.push_back(wall);
    }
}

Wall Game::createGround(int x, int z)
{
    Wall wall;
    wall.setTexture(_Floor_texture);
    wall.setPosition((x - (_mapX / 2)), -1.0f, (z - (_mapY / 2)));
    return (wall);
}

Wall Game::createWall(int x, int z, std::string symb)
{
    Wall wall;
    wall.setTexture(_wall_texture);
    if (symb == "#") {
        wall.setPosition((x - (_mapX / 2)), 0.0f, (z - (_mapY / 2)));
        return (wall);
    }
    wall.setPosition(-1000.0f, -1000.0f, -1000.0f);
    return (wall);
}

Block Game::createBlock(int x, int z, std::string symb)
{
    Block block;

    block.setTexture(_wall_d_texture);
    if (symb == "d") {
        block.setPosition((x - (_mapX / 2)), 0.0f, (z - (_mapY / 2)));
        return (block);
    }
    block.setPosition(-1000.0f, -1000.0f, -1000.0f);
    return (block);
}

void Game::createBonus(int x, int z, std::string symb, Bonus::OBJ type)
{
    if (type == Bonus::NONE)
        return;

    Bonus bonus(type);
    //_bonus.setTexture("path.png");
    bonus.setPosition(x, 0.0f, z);
    //draw un b a cet endroit sur la map.txt
    _bonus.push_back(bonus);
    return;
}

Objects Game::createBomb(int x, int z, std::string symb)
{
    Effect explosion;
    Objects bomb(explosion);

    //_bombs.setTexture("path.png");
    bomb.setPosition(x, 0.0f, z);
    //draw un B a cet endroit sur la map.txt
    _bombs.push_back(bomb);

    return bomb;
}

void Game::setMap(std::string &path)
{
    int z = 0;
    std::string line;
    std::ifstream myfile(path);
    if (myfile.is_open()) {
        while (std::getline(myfile,line)) {
            parseLine(z, line);
            z++;
        }
        myfile.close();
    } else {
        std::cerr << "Game.cpp : Unable to open file";
    }
}

std::vector<Wall> &Game::getWall()
{
    return (_wall);
}

std::vector<Wall> &Game::getGround()
{
    return (_ground);
}

std::vector<Block> &Game::getBlock()
{
    return (_block);
}

std::vector<Bonus> &Game::getBonus()
{
    return (_bonus);
}

std::vector<Objects> &Game::getObj()
{
    return (_bombs);
}

std::vector<Effect> &Game::getEffects()
{
    return (_effects);
}

std::pair<int, int> Game::getMapSize() const
{
    return (std::make_pair(_mapX, _mapY));
}

void Game::setMapSize(int x, int y)
{
    _mapX = x;
    _mapY = y;
}

std::string Game::playerStringGenerate(int size)
{
    std::vector<std::string> token;
    token.push_back(" ");
    token.push_back("d");
    std::string line;
    int random;

    for (int i = 0; i < size; i++) {
        random = std::rand()%2;
        if (i == 0 || i == (size - 1)) {
            line = line + "#";
        } else if (i == 1 || i == (size - 2)) {
            line = line + "p";
        } else if (i == 2 || i == (size - 3)) {
            line = line + " ";
        } else {
            line = line + token[random];;
        }
    }
    return (line);
}

std::string Game::spaceStringGenerate(int size)
{
    std::vector<std::string> token;
    token.push_back(" ");
    token.push_back("d");
    std::string line;
    int random;

    for (int i = 0; i < size; i++) {
        random = std::rand()%2;
        if (i == 0 || i == (size - 1)) {
            line = line + "#";
        } else if (i == 1 || i == (size - 2)) {
            line = line + " ";
        } else if ((i % 2) == 0) {
            line = line + "#";
        } else {
            line = line + token[random];;
        }
    }
    return (line);
}

std::string Game::emptyStringGenerate(int size)
{
    std::vector<std::string> token;
    token.push_back(" ");
    token.push_back("d");
    std::string line;
    int random;

    for (int i = 0; i < size; i++) {
        random = std::rand()%2;
        if (i == 0 || i == (size - 1)) {
            line = line + "#";
        } else {
            line = line + token[random];
        }
    }
    return (line);
}

std::string Game::mixStringGenerate(int size)
{
    std::vector<std::string> token;
    token.push_back(" ");
    token.push_back("d");
    std::string full = "#";
    std::string line;
    int random;

    for (int i = 0; i < size; i++) {
        random = std::rand()%2;
        if (i == 0 || i == (size - 1)) {
            line = line + "#";
        } else if ((i % 2) == 0) {
            line = line + full;
        } else {
            line = line + token[random];;
        }
    }
    return (line);
}

std::string Game::fullStringGenerate(int size)
{
    std::string full;
    for (int i = 0; i < size; i++) {
        full = full + "#";
    }
    return (full);
}

void Game::writeOnFile()
{
    if (monFlux) {
		monFlux << _map << std::endl;
    }
}

void Game::clearMap()
{
    _wall.erase(_wall.begin(), _wall.end());
    _block.erase(_block.begin(), _block.end());
    _ground.erase(_ground.begin(), _ground.end());
    _bonus.erase(_bonus.begin(), _bonus.end());
    _bombs.erase(_bombs.begin(), _bombs.end());
    _effects.erase(_effects.begin(), _effects.end());
}

bool Game::checkWallEffect(float posBx, float posBy, float posBz)
{
    for (auto &n: _wall)
        if (n.GetPosition().x == posBx && n.GetPosition().y == posBy
            && n.GetPosition().z == posBz)
            return false;
    return true;
}

void Game::checkWall(bool lock, float posBx1, float posBx2,
                     float posBy, float posBz1, float posBz2)
{
    if (!lock) {
        if (checkWallEffect(posBx1, posBy, posBz1)) {
            appendEffect(posBx1, posBy, posBz1);
            if (checkWallEffect(posBx2, posBy, posBz2))
                appendEffect(posBx2, posBy, posBz2);
        }
    }
}

void Game::effectBomb(Vector3 posB)
{
    Effect effect;
    effect.setPosition(posB.x, posB.y, posB.z);
    _effects.push_back(effect);
    checkWall(_lockright, posB.x + 1, posB.x + 2, posB.y, posB.z, posB.z);
    checkWall(_lockleft, posB.x - 1, posB.x - 2, posB.y, posB.z, posB.z);
    checkWall(_lockup, posB.x, posB.x, posB.y, posB.z - 1, posB.z - 2);
    checkWall(_lockdown, posB.x, posB.x, posB.y, posB.z + 1, posB.z + 2);
}

void Game::setFalseEffect()
{
    _lockright = false;
    _lockleft = false;
    _lockup = false;
    _lockdown = false;
}

void Game::appendEffect(float posBx, float posBy, float posBz)
{
    Effect effect;
    effect.setPosition(posBx, posBy, posBz);
    _effects.push_back(effect);
}

bool Game::rangeExplosion(Vector3 posB, Vector3 posW)
{
    if (posB.x + 1 == posW.x && posB.z == posW.z && !_lockright) {
        _lockright = true;
        appendEffect(posB.x + 1, posB.y, posB.z);
        return true;
    } else if (!_lockright) {
        if (posB.x + 2 == posW.x && posB.z == posW.z) {
            _lockright = true;
            for (auto &n: _wall) {
                if (posB.z == n.GetPosition().z && posB.x + 1 == n.GetPosition().x) {
                    return false;
                }
            }
            appendEffect(posB.x + 1, posB.y, posB.z);
            appendEffect(posB.x + 2, posB.y, posB.z);
            return true;
        }
    }
    if (posB.x == posW.x && posB.z + 1 == posW.z && !_lockdown) {
        _lockdown = true;
        appendEffect(posB.x, posB.y, posB.z + 1);
        return true;
    } else if (!_lockdown) {
        if (posB.x == posW.x && posB.z + 2 == posW.z) {
            _lockdown = true;
            for (auto &n: _wall) {
                if (posB.z - 1 == n.GetPosition().z && posB.x == n.GetPosition().x) {
                    return false;
                }
            }
            appendEffect(posB.x, posB.y, posB.z + 1);
            appendEffect(posB.x, posB.y, posB.z + 2);
            return true;
        }
    }
    if (posB.x - 1 == posW.x && posB.z == posW.z) {
        _lockleft = true;
        appendEffect(posB.x - 1, posB.y, posB.z);
        return true;
    } else if (posB.x - 1 == posW.x + 1 && posB.z == posW.z) {
        _lockleft = true;
        for (auto &n: _block) {
            if (posB.z == n.GetPosition().z && posB.x - 1 == n.GetPosition().x) {
                appendEffect(posB.x - 1, posB.y, posB.z);
                return false;
            }
        }
        for (auto &n: _wall) {
            if (posB.z == n.GetPosition().z && posB.x - 1 == n.GetPosition().x) {
                return false;
            }
        }
        appendEffect(posB.x - 1, posB.y, posB.z);
        appendEffect(posB.x - 2, posB.y, posB.z);
        return true;
    } else if (posB.x - 2 == posW.x && posB.z == posW.z) {
        appendEffect(posB.x - 1, posB.y, posB.z);
        appendEffect(posB.x - 2, posB.y, posB.z);
        return true;
    }
    if (posB.x == posW.x && posB.z - 1 == posW.z) {
        _lockup = true;
        appendEffect(posB.x, posB.y, posB.z - 1);
        return true;
    } else if (posB.x == posW.x && posB.z - 1 == posW.z + 1) {
        _lockup = true;
        for (auto &n: _block) {
            if (posB.z - 1 == n.GetPosition().z && posB.x == n.GetPosition().x) {
                appendEffect(posB.x, posB.y, posB.z - 1);
                return false;
            }
        }
        for (auto &n: _wall) {
            if (posB.z == n.GetPosition().z - 1 && posB.x == n.GetPosition().x) {
                return false;
            }
        }
        appendEffect(posB.x, posB.y, posB.z - 1);
        appendEffect(posB.x, posB.y, posB.z - 2);
        return true;
    }
    return false;
}

Bonus::OBJ Game::randOnBonus()
{
    int randomSate = std::rand() % 2;
    int randomVal;

    if (randomSate == 0) {
        randomVal = std::rand() % 4;
        if (randomVal == 0)
            return Bonus::BOMB;
        else if (randomVal == 1)
            return Bonus::FIRE;
        else if (randomVal == 2)
            return Bonus::WALL;
        else if (randomVal == 3)
            return Bonus::SPEED;
    }
    return Bonus::NONE;
}

void Game::checkBombsExplosion()
{
    setFalseEffect();
    for (auto itBombs = _bombs.begin(); itBombs != _bombs.end();) {
        if (!itBombs->_hasExplode) {
            ++itBombs;
            continue;
        }
        for (auto itBlocks = _block.begin(); itBlocks != _block.end();) {
            //std::cout << "WALL: X " << itBlocks->GetPosition().x << " Z " << itBlocks->GetPosition().z << std::endl;
            if (rangeExplosion(itBombs->GetPosition(), itBlocks->GetPosition())) {
                createBonus(itBlocks->GetPosition().x, itBlocks->GetPosition().z, "o", randOnBonus());
                itBlocks = _block.erase(itBlocks);
                continue;
            }
            ++itBlocks;
        }
        Effect effect;
        effect.setPosition(itBombs->GetPosition().x, itBombs->GetPosition().y, itBombs->GetPosition().z);
        _effects.push_back(effect);
        effectBomb(itBombs->GetPosition());
        itBombs = _bombs.erase(itBombs);
        setFalseEffect();
    }
}//ca met un effet que quand on casse un bail

void Game::delEffectsByTime()
{
    for (auto it = _effects.begin(); it != _effects.end();) {
        if (it->_hasEffectOff) {
            it = _effects.erase(it);
        } else
            ++it;
    }
}

void Game::updateMap()
{
    checkBombsExplosion();
    delEffectsByTime();
}

void Game::generateMap(std::string mapName)
{
    std::string path;

    if (mapName == "") {
        path = "Assets/Map/map.txt";
    } else {
        path = "Assets/Map/" + mapName;
    }
    monFlux.open(path);
    clearMap();
    for (int i = 0; i < _mapY; i++) {
        if (i == 0 || i == (_mapY - 1)) {
            _map = fullStringGenerate(_mapX);
        } else if (i == 1 || i == (_mapY - 2)) {
            _map = playerStringGenerate(_mapX);
        } else if (i == 2 || i == (_mapY - 3)) {
            _map = spaceStringGenerate(_mapX);
        } else if ((i % 2) == 0) {
            _map = mixStringGenerate(_mapX);
        } else {
            _map = emptyStringGenerate(_mapX);
        }
        writeOnFile();
    }
    monFlux.close();
    setMap(path);
}