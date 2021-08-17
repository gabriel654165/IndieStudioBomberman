/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-gabriel.medoukali
** File description:
** Chrono
*/

#ifndef CHRONO_H
#define CHRONO_H

#include <chrono>

class Timer {
public:
    Timer();
    ~Timer();

    static Timer *Instance();
    static void Release();

    void Reset();
    float DeltaTime();
    void TimeScale(float t = 1.0f);
    float TimeScale();
    void Tick();
private:

    static Timer *sIntsance;

    std::chrono::system_clock::time_point mStartTime;
    std::chrono::duration<float> mDeltaTime;
    float mTimeScale;
};

#endif //CHRONO_H