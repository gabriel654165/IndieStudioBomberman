//
// Created by thomas on 19/06/2021.
//

#ifndef B_YEP_400_PAR_4_1_INDIESTUDIO_GABRIEL_MEDOUKALI_ANIMATEDMODEL_HPP
#define B_YEP_400_PAR_4_1_INDIESTUDIO_GABRIEL_MEDOUKALI_ANIMATEDMODEL_HPP
#include "AMap.hpp"
#include <string>
#include <map>

class AnimatedModel : public AMap {
public:
    explicit AnimatedModel(std::string &);
    ~AnimatedModel() override;
    [[nodiscard]] Model GetModel() const;
    bool Animation(std::string const &);
    [[nodiscard]] std::string const &GetName() const;
    void SetFrameCount(int);
    [[nodiscard]] Vector3 GetIuModelScale() const;
private:
    std::map<std::string, ModelAnimation *> _animationTab;
    Texture2D texture;
    Vector3 _iUModel;
    const std::string _name;
    Model model;
    int animCount;
    int frameCount;
};

#endif //B_YEP_400_PAR_4_1_INDIESTUDIO_GABRIEL_MEDOUKALI_ANIMATEDMODEL_HPP
