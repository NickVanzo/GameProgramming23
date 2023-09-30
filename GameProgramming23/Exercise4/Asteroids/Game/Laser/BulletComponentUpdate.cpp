//
// Created by Nicolò Vanzo on 22/09/23.
//

#include "BulletComponentUpdate.h"
#include "MyEngine.h"

namespace Asteroids {
    using namespace glm;
    BulletComponentUpdate::BulletComponentUpdate(std::shared_ptr<MyEngine::GameObject> parent) {
        _gameObject = parent;
    }
    void BulletComponentUpdate::Update(float deltaTime) {
        MoveLaser();
    }
    void BulletComponentUpdate::MoveLaser() {
        std::weak_ptr<MyEngine::GameObject> parent = GetGameObject();
        if(parent.lock()->position.x == 0 && parent.lock()->position.y == 0) {
            parent.lock().get()->position = startingPos_;
        }
        float rotationInRadians = radians(parent.lock().get()->rotation + 90);
        vec2 direction = vec2(cos(rotationInRadians), sin(rotationInRadians));
        parent.lock().get()->position += direction * bulletSpeed;
        parent.lock().get()->rotation = rotation_;
    }

    void BulletComponentUpdate::SetStartingPos(glm::vec2 initialPos) {
        startingPos_ = initialPos;
    }
    void BulletComponentUpdate::SetRotation(float rotation) {
        rotation_ = rotation;
    }
}
