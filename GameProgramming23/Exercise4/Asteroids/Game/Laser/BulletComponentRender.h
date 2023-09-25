//
// Created by Nicolò Vanzo on 22/09/23.
//
#include "Engine/Component.h"
#include "Engine/GameObject.h"
#pragma once
namespace Asteroids {
    class BulletComponentRender: public MyEngine::Component{
    public:
        sre::Sprite sprite;
        glm::vec2 startingPos_;
        float rotation_;
        float bulletSpeed = 10;
        void SetRotation(float rotation);
        void SetStartingPos(glm::vec2);
        void Render(sre::SpriteBatch::SpriteBatchBuilder&) override;
    private:
        void MoveLaser(MyEngine::GameObject *);
    };
}


