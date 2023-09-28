//
// Created by Nicolò Vanzo on 22/09/23.
//
#include "Engine/Component.h"
#include "BulletComponentRender.h"
namespace Asteroids {
    using namespace glm;
    void BulletComponentRender::Render(sre::SpriteBatch::SpriteBatchBuilder & builder) {
        std::weak_ptr<MyEngine::GameObject> parent = GetGameObject();
        if(parent.lock().get()) {
            sprite.setPosition(parent.lock().get()->position);
            sprite.setRotation(parent.lock().get()->rotation);
            builder.addSprite(sprite);
        }
    }
}