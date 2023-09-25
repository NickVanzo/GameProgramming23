//
// Created by Nicolò Vanzo on 25/09/23.
//

#include "GameObject.h"
#include "Component.h"
#pragma once
namespace Asteroids {
    class AsteroidSpawner: public MyEngine::Component {
        public:
        void Update(float deltaTime);
        void SpawnAsteroid();
    private:
        std::list<MyEngine::GameObject*> asteroids;
        float TIME_TO_SPAWN_ASTEROID = 2;
        float timeCounter = 0;
    };
}


