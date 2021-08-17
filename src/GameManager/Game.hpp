/*
** EPITECH PROJECT, 2021
** Indie studio
** File description:
** Game
*/

#ifndef GAME_H
#define GAME_H
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>

#include "../Lib/Map/Static/Block.hpp"
#include "../Lib/Map/Static/Wall.hpp"
#include "../Lib/Map/Static/Objects.hpp"
#include "../Lib/Map/Static/Bonus.hpp"

class Game {
public:
    Game();
    Game(int sizeX, int SizeY);
    ~Game();
    void generateMap(std::string mapName);
    void updateMap();
    void setMapSize(int sizeX, int sizeY);
    std::pair<int, int> getMapSize() const;
    void setMap(std::string &path);
    void clearMap();
    /*write save in file*/
    void writeOnFile();
    std::string fullStringGenerate(int size);
    std::string mixStringGenerate(int size);
    std::string emptyStringGenerate(int size);
    std::string playerStringGenerate(int size);
    std::string spaceStringGenerate(int size);
    void parseLine(int z, std::string line);

    /*MAP VECTORS*/
    Wall createWall(int x, int z, std::string symb);
    Wall createGround(int x, int z);
    Block createBlock(int x, int z, std::string symb);
    void createBonus(int x, int z, std::string symb, Bonus::OBJ type);
    Bonus::OBJ randOnBonus();
    Objects createBomb(int x, int z, std::string symb);
    std::vector<Block> &getBlock();
    std::vector<Wall> &getWall();
    std::vector<Wall> &getGround();
    std::vector<Bonus> &getBonus();
    std::vector<Objects> &getObj();
    std::vector<Effect> &getEffects();
    std::vector<Block> _block;
    std::vector<Wall> _wall;
    std::vector<Wall> _ground;
    std::vector<Objects> _bombs;
    std::vector<Bonus> _bonus;
    std::vector<Effect> _effects;
    /* BOMB EFFECT */
    void delEffectsByTime();
    void setFalseEffect();
    void effectBomb(Vector3 posB);
    bool checkWallEffect(float posBx, float posBy, float posBz);
    void checkWall(bool lock, float posBx1, float posBx2,
                   float posBy, float posBz1, float posBz2);
    void checkBombsExplosion();
    bool rangeExplosion(Vector3 posB, Vector3 posW);
    void appendEffect(float posBx, float posBy, float posBz);
    bool _lockright;
    bool _lockleft;
    bool _lockup;
    bool _lockdown;

private:
    std::string _map;

    int _mapX;
    int _mapY;
    std::ofstream monFlux;

    Texture2D _wall_texture;
    Texture2D _wall_d_texture;
    Texture2D _Floor_texture;
};


#endif //GAME_H
