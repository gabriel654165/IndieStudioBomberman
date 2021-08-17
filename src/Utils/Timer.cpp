/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-gabriel.medoukali
** File description:
** Chrono
*/

#include "Timer.hpp"

Timer::Timer()
{
    Reset();
    mTimeScale = 1.0f;
    mDeltaTime = std::chrono::duration<float>(0.0f);
}

Timer::~Timer()
{

}

Timer *Timer::sIntsance = nullptr;

Timer *Timer::Instance()
{
    if (sIntsance == nullptr)
        sIntsance = new Timer();
    return new Timer;
}

void Timer::Release()
{
    delete sIntsance;
    sIntsance = nullptr;
}

void Timer::Reset()
{
    mStartTime = std::chrono::system_clock::now();
}

float Timer::DeltaTime()
{
    return mDeltaTime.count();
}

void Timer::TimeScale(float t)
{
    mTimeScale = t;
}

float Timer::TimeScale()
{
    return mTimeScale;
}

void Timer::Tick()
{
    mDeltaTime = std::chrono::system_clock::now() - mStartTime;
}
