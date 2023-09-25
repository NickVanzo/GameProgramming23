//
// Created by Nicolò Vanzo on 25/09/23.
//
#include "Engine/Component.h"
#include "AsteroidSpawner.h"

namespace Asteroids {
    using namespace glm;
    using namespace std;
    void AsteroidSpawner::Update(float deltaTime) {
        timeCounter -= deltaTime;
        if(timeCounter < 0) {
            timeCounter = TIME_TO_SPAWN_ASTEROID;
        }
    }
}