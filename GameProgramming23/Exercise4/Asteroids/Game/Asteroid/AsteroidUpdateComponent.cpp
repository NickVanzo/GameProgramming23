//
// Created by Nicolò Vanzo on 25/09/23.
//

#include "AsteroidUpdateComponent.h"
#include "../Enums/AsteroidSpawnerPositions.h"
#pragma once
namespace Asteroids {
    using namespace glm;
    void AsteroidUpdateComponent::SetDirection(int direction) {
        this->direction = direction;
    }
    void AsteroidUpdateComponent::Update(float deltaTime) {
        MyEngine::GameObject* parent = GetGameObject();
        if(direction == LOWER) {
            parent->position += velocity;
        } else if(direction == UPPER) {
            parent->position -= velocity;
        } else {}
        parent->rotation += + 1 * speed;
    }
}