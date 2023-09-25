//
// Created by Nicolò Vanzo on 22/09/23.
//

#include "BulletComponentUpdate.h"
#include "MyEngine.h"

namespace Asteroids {
    using namespace glm;
    void BulletComponentUpdate::Update(float deltaTime) {
        MoveLaser();
    }
    void BulletComponentUpdate::MoveLaser() {
        MyEngine::GameObject* parent = GetGameObject();
        if(parent->position.x == 0 && parent->position.y == 0) {
            parent->position = startingPos_;
        }
        float rotationInRadians = radians(parent->rotation + 90);
        vec2 direction = vec2(cos(rotationInRadians), sin(rotationInRadians));
        parent->position += direction * bulletSpeed;
        parent->rotation = rotation_;
    }

    void BulletComponentUpdate::SetStartingPos(glm::vec2 initialPos) {
        startingPos_ = initialPos;
    }
    void BulletComponentUpdate::SetRotation(float rotation) {
        rotation_ = rotation;
    }
}
