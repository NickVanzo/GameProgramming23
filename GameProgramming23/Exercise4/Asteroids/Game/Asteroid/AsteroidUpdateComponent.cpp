//
// Created by Nicolò Vanzo on 25/09/23.
//

#include "AsteroidUpdateComponent.h"
#include "../Enums/AsteroidSpawnerPositions.h"
#pragma once
namespace Asteroids {
    using namespace glm;
    AsteroidUpdateComponent::AsteroidUpdateComponent(std::weak_ptr<MyEngine::GameObject> p) {
        _gameObject = p;
    }
    void AsteroidUpdateComponent::SetDirection(int direction) {
        this->direction = direction;
    }
    void AsteroidUpdateComponent::Update(float deltaTime) {
        std::weak_ptr<MyEngine::GameObject> parent = GetGameObject();
        if(direction == LOWER) {
            parent.lock().get()->position += velocity;
        } else if(direction == UPPER) {
            parent.lock().get()->position -= velocity;
        } else {}
        parent.lock().get()->rotation += + 1 * speed;
    }
}