//
// Created by Nicolò Vanzo on 25/09/23.
//

#include "GameObject.h"
#include "Component.h"
#pragma once
namespace Asteroids {
    class AsteroidSpawner: public MyEngine::Component {
        public:
        AsteroidSpawner(int);
        void Update(float deltaTime);
        void SpawnAsteroid();
        void CheckAsteroidCollisionWithBounderies();
    private:
        std::list<MyEngine::GameObject*> asteroids;
        float TIME_TO_SPAWN_ASTEROID = 20;
        float timeCounter = 0;
        int direction;
    };
}


