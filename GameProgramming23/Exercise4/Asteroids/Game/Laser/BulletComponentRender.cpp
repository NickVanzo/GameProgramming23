//
// Created by Nicolò Vanzo on 22/09/23.
//
#include "Engine/Component.h"
#include "BulletComponentRender.h"
namespace Asteroids {
    void BulletComponentRender::Render(sre::SpriteBatch::SpriteBatchBuilder & builder) {
        MyEngine::GameObject *parent = GetGameObject();
        glm::vec2 basePos = startingPos_;
        sprite.setPosition(basePos +  parent->position);
        sprite.setRotation(parent->rotation);
        builder.addSprite(sprite);
    }
    void BulletComponentRender::SetStartingPos(glm::vec2 initialPos) {
        startingPos_ = initialPos;
    }
}