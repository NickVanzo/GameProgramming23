//
// Created by Nicolò Vanzo on 25/09/23.
//

#include "GameObject.h"
#pragma once
namespace Asteroids {
    class AsteroidSpawner: public MyEngine::Component {
        public:
        void Update(float deltaTime);
    private:
        float TIME_TO_SPAWN_ASTEROID = 10;
        float timeCounter = 0;
    };
}


