//
// Created by Nicolò Vanzo on 25/09/23.
//

#include "AsteroidUpdateComponent.h"
#pragma once
namespace Asteroids {
    using namespace glm;
    void AsteroidUpdateComponent::SetDirection(int direction) {
        this->direction = direction;
    }
    void AsteroidUpdateComponent::Update(float deltaTime) {
        MyEngine::GameObject* parent = GetGameObject();
        vec2 velocity = vec2(rand() % 5 + 1,rand() % 5 + 1);
        if(direction == 0) {
            parent->position += velocity;
        } else {
            parent->position -= velocity;
        }
        parent->rotation += + 1 * speed;
    }
}