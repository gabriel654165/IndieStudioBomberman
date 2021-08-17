/*
** EPITECH PROJECT, 2024
** B_YEP_400_PAR_4_1_indiestudio_gabriel_medoukali
** File description:
** Audio.cpp
*/

#include "Audio.hpp"

Audio::Audio()
{
    InitAudioDevice();
    if (!IsAudioDeviceReady()) {
        std::cerr << "Error while initialising audio device" << std::endl;
    }
    SetMasterVolume(0.3f);
    _volume = 0.3f;
}

Audio::~Audio()
{
    /*for (const auto &it : _musics) {
        UnloadMusicStream(it.second.music);
    }
    for (const auto &it : _soundEffects) {
        UnloadSound(it.second);
    }
    StopSoundMulti();
    CloseAudioDevice();*/
}

void Audio::addSound(const int key, const std::string &path)
{
    _soundEffects.insert_or_assign(key, LoadSound(path.c_str()));
}

void Audio::delSound(const int key)
{
    if (!checkSound(key)) {
        std::cerr << "Sound not found" << std::endl;
        return;
    }
    UnloadSound(_soundEffects.at(key));
    _soundEffects.erase(key);
}

void Audio::addMusic(const int key, const std::string &path)
{
    Music_t tmp = {LoadMusicStream(path.c_str()), false};

    _musics.insert_or_assign(key, tmp);
}

void Audio::delMusic(const int key)
{
    if (!checkMusic(key)) {
        std::cerr << "Music not found" << std::endl;
        return;
    }
    UnloadMusicStream(_musics.at(key).music);
    _musics.erase(key);
}

void Audio::playSound(const int key)
{
    if (!checkSound(key)) {
        std::cerr << "Sound not found" << std::endl;
        return;
    }
    PlaySoundMulti(_soundEffects.at(key));
}

void Audio::stopSound(const int key)
{
    if (!checkSound(key)) {
        std::cerr << "Sound not found" << std::endl;
        return;
    }
    PauseSound(_soundEffects.at(key));
}

void Audio::playMusic(const int key)
{
    stopAllMusics();
    if (!checkMusic(key)) {
        std::cerr << "Music not found" << std::endl;
        return;
    }
    PlayMusicStream(_musics.at(key).music);
}

void Audio::stopMusic(const int key)
{
    if (!checkMusic(key)) {
        std::cerr << "Music not found" << std::endl;
        return;
    }
    StopMusicStream(_musics.at(key).music);
}

void Audio::pauseOrResumeMusic(const int key)
{
    if (!checkMusic(key)) {
        std::cerr << "Music not found" << std::endl;
        return;
    }
    _musics.at(key).paused = !_musics.at(key).paused;
    if (_musics.at(key).paused)
        PauseMusicStream(_musics.at(key).music);
    else
        ResumeMusicStream(_musics.at(key).music);
}

void Audio::restartMusic(const int key)
{
    if (!checkMusic(key)) {
        std::cerr << "Music not found" << std::endl;
        return;
    }
    StopMusicStream(_musics.at(key).music);
    PlayMusicStream(_musics.at(key).music);
}

bool Audio::checkMusic(const int key)
{
    return (_musics.find(key) != _musics.end());
}

bool Audio::checkSound(const int key)
{
    return (_soundEffects.find(key) != _soundEffects.end());
}

void Audio::setVolume(float value)
{
    SetMasterVolume(value);
    _volume = value;
}

float Audio::getVolume() const
{
    return (_volume);
}

void Audio::updateMusic()
{
    for (const auto &it : _musics) {
        UpdateMusicStream(it.second.music);
    }
}

void Audio::setMusicLoop(const int key, bool isLooping)
{
    if (!checkMusic(key)) {
        std::cerr << "Music not found" << std::endl;
        return;
    }
    _musics.at(key).music.looping = isLooping;
}

void Audio::stopAllMusics()
{
    for (const auto &it : _musics) {
        StopMusicStream(it.second.music);
    }
}
