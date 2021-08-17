/*
** EPITECH PROJECT, 2024
** B_YEP_400_PAR_4_1_indiestudio_gabriel_medoukali
** File description:
** Audio.hpp
*/
#ifndef B_YEP_400_PAR_4_1_INDIESTUDIO_GABRIEL_MEDOUKALI_AUDIO_HPP
#define B_YEP_400_PAR_4_1_INDIESTUDIO_GABRIEL_MEDOUKALI_AUDIO_HPP

#include <unordered_map>
#include <iostream>
#include <string>

#include "raylib.h"

typedef struct Music_s
{
    Music music;
    bool paused;
} Music_t;

enum MUSIC {
    START_MENU,
    PAUSE_MENU,
    INGAME,
    WIN_SCREEN,
    LOOSE_SCREEN
};

enum SOUND {
    EXPLOSION,
    CLICK1,
    CLICK2,
    CLICK3,
    DEAD,
    BOMB,
    KILL
};

class Audio
{
public:
    Audio();
    ~Audio();

    void addSound(const int key, const std::string &path);
    void delSound(const int key);
    void addMusic(const int key, const std::string &path);
    void delMusic(const int key);
    void playSound(const int key);
    void stopSound(const int key);
    void playMusic(const int key);
    void stopMusic(const int key);
    void pauseOrResumeMusic(const int key);
    void restartMusic(const int key);
    void setVolume(float value);
    float getVolume() const;
    void updateMusic();
    void setMusicLoop(const int key, bool isLooping);
protected:
private:
    bool checkMusic(const int key);
    bool checkSound(const int key);
    void stopAllMusics();
    std::unordered_map<int, Music_t> _musics;
    std::unordered_map<int, Sound> _soundEffects;
    float _volume;
};


#endif //B_YEP_400_PAR_4_1_INDIESTUDIO_GABRIEL_MEDOUKALI_AUDIO_HPP