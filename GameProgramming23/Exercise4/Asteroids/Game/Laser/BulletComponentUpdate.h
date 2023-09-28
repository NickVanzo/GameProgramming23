//
// Created by Nicolò Vanzo on 22/09/23.
//
#include "Engine/Component.h"
#pragma once

namespace Asteroids{
    class BulletComponentUpdate: public MyEngine::Component {
    public:
        BulletComponentUpdate(std::shared_ptr<MyEngine::GameObject>);
        float bulletSpeed = 10;
        float time = 0.0;
        void SetRotation(float rotation);
        void SetStartingPos(glm::vec2);
        void Update(float deltaTime) override;
    private:
        void MoveLaser();
        glm::vec2 startingPos_;
        float rotation_;
    };
}


