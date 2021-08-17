//
// Created by thomas on 19/06/2021.
//

#include "AnimatedModel.hpp"
#include <iostream>

AnimatedModel::AnimatedModel(std::string &name) : _name(name)
{
    frameCount = 0;
    animCount = 0;
    if (_name == "wiiFit") {
        _iUModel = (Vector3){0.06, 0.06, 0.06};
        _scale = (Vector3) {0.1f, 0.1f, 0.1f};
        texture = LoadTexture("Assets/ressources/def_wiifit_001_col.png");
        _animationTab["idle"] = LoadModelAnimations("Assets/ressources/wiifitIdle.iqm", &animCount);
        _animationTab["runLeft"] = LoadModelAnimations("Assets/ressources/wiifitRunLeft.iqm", &animCount);
        _animationTab["runRight"] = LoadModelAnimations("Assets/ressources/wiifitRunRight.iqm", &animCount);
        _animationTab["runBack"] = LoadModelAnimations("Assets/ressources/wiifitRunBack.iqm", &animCount);
        _animationTab["runForward"] = LoadModelAnimations("Assets/ressources/wiifitRunForward.iqm", &animCount);
        _animationTab["jump"] = LoadModelAnimations("Assets/ressources/wiifitJump.iqm", &animCount);
        _animationTab["dance"] = LoadModelAnimations("Assets/ressources/wiifitDance.iqm", &animCount);
        model = LoadModel("Assets/ressources/wiifitModel.iqm");
        SetMaterialTexture(&model.materials[0], MAP_DIFFUSE, texture);
    } else if (_name == "mouse") {
        _iUModel = (Vector3){0.005, 0.005, 0.005};
        _scale = (Vector3) {0.01f, 0.01f, 0.01f};
        texture = LoadTexture("Assets/ressources/Ch14_1001_Diffuse.png");
        _animationTab["idle"] = LoadModelAnimations("Assets/ressources/idle.iqm", &animCount);
        _animationTab["runLeft"] = LoadModelAnimations("Assets/ressources/runLeftUnmoving.iqm", &animCount);
        _animationTab["runRight"] = LoadModelAnimations("Assets/ressources/runRightUnmoving.iqm", &animCount);
        _animationTab["runBack"] = LoadModelAnimations("Assets/ressources/runBack.iqm", &animCount);
        _animationTab["runForward"] = LoadModelAnimations("Assets/ressources/runForwardUnmoving.iqm", &animCount);
//        jump = LoadModelAnimations("Assets/ressources/.iqm", &animCount);
        _animationTab["dance"] = LoadModelAnimations("Assets/ressources/mouseDancing.iqm", &animCount);
        model = LoadModel("Assets/ressources/mouseModel.iqm");
        SetMaterialTexture(&model.materials[0], MAP_DIFFUSE, texture);
    } else if (_name == "dora") {
        _iUModel = (Vector3){0.05, 0.05, 0.05};
        _scale = (Vector3) {0.07f, 0.07f, 0.07f};
        texture = LoadTexture("Assets/ressources/t0011_0.png");
        _animationTab["idle"] = LoadModelAnimations("Assets/ressources/doraIdle.iqm", &animCount);
        _animationTab["runLeft"] = LoadModelAnimations("Assets/ressources/doraRunLeft.iqm", &animCount);
        _animationTab["runRight"] = LoadModelAnimations("Assets/ressources/doraRunRight.iqm", &animCount);
        _animationTab["runBack"] = LoadModelAnimations("Assets/ressources/doraRunBack.iqm", &animCount);
        _animationTab["runForward"] = LoadModelAnimations("Assets/ressources/doraRunForward.iqm", &animCount);
        _animationTab["jump"] = LoadModelAnimations("Assets/ressources/doraJump.iqm", &animCount);
        _animationTab["dance"] = LoadModelAnimations("Assets/ressources/doraDance.iqm", &animCount);
        model = LoadModel("Assets/ressources/doraModel.iqm");
        SetMaterialTexture(&model.materials[0], MAP_DIFFUSE, texture);
    } else if (_name == "trump") {
        _iUModel = (Vector3){0.5, 0.5, 0.5};
        _scale = (Vector3) {0.7f, 0.7f, 0.7f};
        texture = LoadTexture("Assets/ressources/Trump_DIFF2.tga.png");
        _animationTab["idle"] = LoadModelAnimations("Assets/ressources/trumpIdle.iqm", &animCount);
        _animationTab["runLeft"] = LoadModelAnimations("Assets/ressources/trumpRunLeft.iqm", &animCount);
        _animationTab["runRight"] = LoadModelAnimations("Assets/ressources/trumpRunRight.iqm", &animCount);
        _animationTab["runBack"] = LoadModelAnimations("Assets/ressources/trumpRunBack.iqm", &animCount);
        _animationTab["runForward"] = LoadModelAnimations("Assets/ressources/trumpRunForward.iqm", &animCount);
        _animationTab["jump"] = LoadModelAnimations("Assets/ressources/trumpJump.iqm", &animCount);
        _animationTab["dance"] = LoadModelAnimations("Assets/ressources/trumpDance.iqm", &animCount);
        model = LoadModel("Assets/ressources/trumpModel.iqm");
        SetMaterialTexture(&model.materials[0], MAP_DIFFUSE, texture);
    }
}

AnimatedModel::~AnimatedModel()
{
    for (auto &[key, value]: _animationTab)
        UnloadModelAnimation(*value);
//    UnloadMaterial(model.materials[0]);
    UnloadModel(model);
}

Model AnimatedModel::GetModel() const
{
    return model;
}

bool AnimatedModel::Animation(const std::string &animationName)
{
    frameCount++;
    UpdateModelAnimation(model, _animationTab[animationName][0], frameCount);
    if (frameCount >= _animationTab[animationName][0].frameCount) {
        frameCount = 0;
        return true;
    }
    return false;
}

std::string const &AnimatedModel::GetName() const
{
    return _name;
}

void AnimatedModel::SetFrameCount(int setValue)
{
    frameCount = setValue;
}

Vector3 AnimatedModel::GetIuModelScale() const {
    return _iUModel;
}
