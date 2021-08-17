/*
** EPITECH PROJECT, 2021
** Indie studio
** File description:
** Parser
*/

#ifndef I_TRANSFORM_HPP_
#define I_TRANSFORM_HPP_

#include "raylib.h"

class ITransform {
public:
    virtual ~ITransform() = default;
    virtual Vector3 GetScale() const = 0;
    virtual void setPosition(float x, float y, float z) = 0;
    virtual Vector3 GetPosition() const = 0;
    virtual void setRotation(float x, float y, float z) = 0;
    virtual Vector3 GetRotation() const = 0;
    virtual void setState(bool state) = 0;
    virtual bool GetState() const = 0;
};


#endif //I_TRANSFORM_HPP_
