//
// Created by Nicolò Vanzo on 22/09/23.
//
#include "Engine/Component.h"
#include "BulletComponentRender.h"
namespace Asteroids {
    using namespace glm;
    void BulletComponentRender::Render(sre::SpriteBatch::SpriteBatchBuilder & builder) {
        MyEngine::GameObject *parent = GetGameObject();

        MoveLaser(parent);

        sprite.setPosition(parent->position);
        sprite.setRotation(rotation_);

        builder.addSprite(sprite);
    }
    void BulletComponentRender::MoveLaser(MyEngine::GameObject* parent) {
        if(parent->position.x == 0 && parent->position.y == 0) {
            parent->position = startingPos_;
        }
        float rotationInRadians = radians(parent->rotation + 90);
        vec2 direction = vec2(cos(rotationInRadians), sin(rotationInRadians));
        parent->position += direction * bulletSpeed;
        parent->rotation = rotation_;
    }

    void BulletComponentRender::SetStartingPos(glm::vec2 initialPos) {
        startingPos_ = initialPos;
    }
    void BulletComponentRender::SetRotation(float rotation) {
        rotation_ = rotation;
    }
}