//
// Created by Nicolò Vanzo on 22/09/23.
//
#include "Engine/Component.h"

#ifndef SIMPLERENDERENGINEPROJECT_PLAYERCOMPONENTINPUT_H
#define SIMPLERENDERENGINEPROJECT_PLAYERCOMPONENTINPUT_H
namespace Asteroids {
    class PlayerComponentInput: public MyEngine::Component {
        const float ROT_SPEED = 50;
        const float MOV_SPEED = 5;
        const float MOV_AMOUNT = 20;
        const glm::vec2 movDirection = glm::vec2(1,0);
    public:
        glm::vec2 position;
        float rotation;

        void Init() override;
        void Update(float) override;
    };
}
#endif //SIMPLERENDERENGINEPROJECT_PLAYERCOMPONENTINPUT_H
