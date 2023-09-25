//
// Created by Nicolò Vanzo on 25/09/23.
//
#include "Component.h"
#pragma once
namespace Asteroids {
    class AsteroidUpdateComponent: public MyEngine::Component {
    public:
        void Update(float deltaTime) override;
        void SetDirection(int);
    private:
        int direction = 1;
        int MAX_SPPED = 10;
        float speed = rand() % MAX_SPPED + 1;
    };
}

