/*
** EPITECH PROJECT, 2021
** Indie studio
** File description:
** Parser
*/

#ifndef A_IU_HPP
#define A_IU_HPP

#include "../ITransform.hpp"

class AIu : public ITransform {
public:
    AIu() = default;
    explicit AIu(Vector2 pos);
    ~AIu() override;
    Vector3 GetScale() const override;
    void setPosition(float x, float y, float z) override;
    Vector3 GetPosition() const override;
    void setRotation(float x, float y, float z) override;
    Vector3 GetRotation() const override;
    void setState(bool state) override;
    bool GetState() const override;

    virtual void poolEvent(Vector2 mousePos) = 0;
    virtual void draw() = 0;
protected:
    Vector2 _pos;
    Vector3 _scale;
    bool _state;
};

#endif //A_IU_HPP
