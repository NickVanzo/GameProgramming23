//
// Created by Nicolò Vanzo on 25/09/23.
//
#include "Component.h"
#pragma once
namespace Asteroids {
    using namespace glm;
    class AsteroidUpdateComponent: public MyEngine::Component {
    public:
        AsteroidUpdateComponent(std::weak_ptr<MyEngine::GameObject>);
        void Update(float deltaTime) override;
        void SetDirection(int);
    private:
        int direction = 1;
        int MAX_SPPED = 60;
        float speed = rand() % MAX_SPPED + 1;
        vec2 velocity = vec2((rand() % 10) - 5,rand() % 5 + 1);
    };
}

