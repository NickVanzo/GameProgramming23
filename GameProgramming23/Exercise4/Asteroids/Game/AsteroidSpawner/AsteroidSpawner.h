//
// Created by Nicolò Vanzo on 25/09/23.
//

#include "GameObject.h"
#include "Component.h"
#pragma once
namespace Asteroids {
    class AsteroidSpawner: public MyEngine::Component {
    public:
        AsteroidSpawner(int, std::weak_ptr<MyEngine::GameObject> player, std::weak_ptr<MyEngine::GameObject> parent);
        void Update(float deltaTime);
        void SpawnAsteroid();
        std::vector<std::shared_ptr<MyEngine::GameObject>> CheckAsteroidCollisionWithBounderies();
    private:
        bool IsCollidingWithPlayer(float, float);
        void HandleCollisionWithPlayer();
        void DisabledPlayerRender(std::list< std::shared_ptr<Component>>&);
        void DisabledPlayerMovement(std::list< std::shared_ptr<Component>>&);
        std::weak_ptr<MyEngine::GameObject> player_;
        std::weak_ptr<MyEngine::GameObject> asteroids;
        float TIME_TO_SPAWN_ASTEROID = 2;
        float timeCounter = 0;
        int direction;
        float asteroidsRadius = 90.0f;
    };
}


