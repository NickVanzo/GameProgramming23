//
// Created by Nicolò Vanzo on 25/09/23.
//

#include "GameObject.h"
#include "Component.h"

#pragma once
namespace Asteroids {
    class AsteroidSpawner: public MyEngine::Component {
    public:
        AsteroidSpawner(int, std::shared_ptr<MyEngine::GameObject> player, std::weak_ptr<MyEngine::GameObject> parent);
        void Update(float deltaTime);
        void SpawnAsteroid();
        std::vector<std::shared_ptr<MyEngine::GameObject>> CheckAsteroidCollisionWithBounderiesOrPlayer();
        std::vector<std::shared_ptr<MyEngine::GameObject>> ChecksAsteroidCollisionsWithLasers();
    private:
        bool IsCollidingWithPlayer(float, float);
        void HandleCollisionWithPlayer();
        void DisabledPlayerRender(std::vector< std::shared_ptr<Component>>&);
        void DisabledPlayerMovement(std::vector< std::shared_ptr<Component>>&);
        std::shared_ptr<MyEngine::GameObject> player;
        float TIME_TO_SPAWN_ASTEROID = 1;
        float timeCounter = 0;
        int direction;
        float asteroidsRadius = 120.0f;
    };
}


