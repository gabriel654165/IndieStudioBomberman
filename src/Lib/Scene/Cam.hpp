/*
** EPITECH PROJECT, 2021
** Indie studio
** File description:
** Scene
*/

#ifndef CAM_H
#define CAM_H

#include "../ITransform.hpp"

class Cam : public ITransform {
public:
    Cam();
    ~Cam() override;

    void setState(bool state) override;
    void setRotation(float x, float y, float z) override;//target
    void setPosition(float x, float y, float z) override;
    void setCameraMode(int cameraMode);

    bool GetState() const override;
    Vector3 GetRotation() const override;//target
    Vector3 GetPosition() const override;
    Vector3 GetScale() const override;
    int GetCameraMode();
    Camera &getCamera();

    void poolEvent();
    void updateCamera();
private:
    Camera3D _camera;
    Vector3 _cameraTarget;
    Vector3 _cameraPos;
    Vector3 _cameraUp;
    float _cameraFovy;
    int _cameraMode;
    bool _state;
    Vector3 _scale;
};

//image on veut plusierus fenetres ...

#endif //!CAM_h