//
// Created by Nicolò Vanzo on 22/09/23.
//
#include "Engine/Component.h"
#include "BulletComponentRender.h"
namespace Asteroids {
    using namespace glm;
    void BulletComponentRender::Render(sre::SpriteBatch::SpriteBatchBuilder & builder) {
        std::shared_ptr<MyEngine::GameObject> parent = GetGameObject();
        sprite.setPosition(parent->position);
        sprite.setRotation(parent->rotation);
        builder.addSprite(sprite);
    }
}