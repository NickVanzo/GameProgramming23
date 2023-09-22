//
// Created by Nicolò Vanzo on 22/09/23.
//
#include "Engine/Component.h"
#pragma once
namespace Asteroid {
    class BulletComponentRender: MyEngine::Component{
    public:
        sre::Sprite sprite;
        void Render(sre::SpriteBatch::SpriteBatchBuilder&) override;
    };
}


