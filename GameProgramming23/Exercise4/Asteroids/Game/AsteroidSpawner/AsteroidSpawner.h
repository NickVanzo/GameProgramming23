//
// Created by Nicolò Vanzo on 25/09/23.
//

#include "GameObject.h"
#include "Component.h"
#pragma once
namespace Asteroids {
    class AsteroidSpawner: public MyEngine::Component {
    public:
        AsteroidSpawner(int, MyEngine::GameObject&);
        void Update(float deltaTime);
        void SpawnAsteroid();
        void CheckAsteroidCollisionWithBounderies();
    private:
        bool IsCollidingWithPlayer(float, float);
        void HandleCollisionWithPlayer();
        void DisabledPlayerRender(std::list< std::shared_ptr<Component>>&);
        void DisabledPlayerMovement(std::list< std::shared_ptr<Component>>&);
        MyEngine::GameObject& player_;
        std::list<MyEngine::GameObject*> asteroids;
        float TIME_TO_SPAWN_ASTEROID = 20;
        float timeCounter = 0;
        int direction;
        float asteroidsRadius = 90.0f;
    };
}


