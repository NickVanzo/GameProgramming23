//
// Created by Nicolò Vanzo on 22/09/23.
//
#include "Engine/Component.h"
#include "Engine/GameObject.h"
#pragma once
namespace Asteroids {
    class BulletComponentRender: public MyEngine::Component{
    public:
        BulletComponentRender(std::shared_ptr<MyEngine::GameObject>);
        sre::Sprite sprite;
        void Render(sre::SpriteBatch::SpriteBatchBuilder&) override;
    };
}


