/*
** EPITECH PROJECT, 2021
** Indie studio
** File description:
** Parser
*/

#ifndef A_MAP_HPP
#define A_MAP_HPP

#include "../ITransform.hpp"
#include <string>

class AMap : public ITransform {
public:
    AMap() = default;
    ~AMap() = default;
    void SetId();
    [[nodiscard]] unsigned long GetId() const;
    void setPosition(float x, float y, float z) override;
    Vector3 GetPosition() const override;
    void setRotation(float x, float y, float z) override;
    Vector3 GetRotation() const override;
    void setState(bool state) override;
    bool GetState() const override;
    Vector3 GetScale() const override;
    //void colapse();
protected:
    unsigned long _id;
    Vector3 _position;
    Vector3 _rotation;
    Vector3 _scale;
    bool state;
private:
    int posX;
    int posY;
    bool isTrigger;
};

#endif //A_MAP_HPP
