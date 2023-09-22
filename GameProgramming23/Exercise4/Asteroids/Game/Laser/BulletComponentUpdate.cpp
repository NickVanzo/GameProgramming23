//
// Created by Nicolò Vanzo on 22/09/23.
//

#include "BulletComponentUpdate.h"
#include "MyEngine.h"

namespace Asteroid {
    void BulletComponentUpdate::Update(float deltaTime) {
        MyEngine::GameObject* parent = GetGameObject();
        glm::vec2 basePos = parent->position;
    }
}
