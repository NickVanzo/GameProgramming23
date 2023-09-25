//
// Created by Nicolò Vanzo on 25/09/23.
//
#include "AsteroidSpawner.h"
#include "../Asteroid/AsteroidRenderComponent.h"
#include "MyEngine.h"
#include <cstdlib>

namespace Asteroids {
    using namespace glm;
    using namespace std;
    void AsteroidSpawner::Update(float deltaTime) {
        timeCounter -= deltaTime;
        if(timeCounter < 0) {
            SpawnAsteroid();
            timeCounter = TIME_TO_SPAWN_ASTEROID;
        }
    }
    void AsteroidSpawner::SpawnAsteroid() {
        MyEngine::Engine* engine = MyEngine::Engine::GetInstance();
        auto gameObject = engine->CreateGameObject("asteroid");
        auto asteroidRenderComponent = std::shared_ptr<Asteroids::AsteroidRenderComponent>(new Asteroids::AsteroidRenderComponent());
        asteroidRenderComponent->sprite = engine->GetSpriteFromAtlas("meteorBrown_big1.png");
        gameObject->rotation = (rand() % 360) - 180;
        float randX = rand() % 1600;
        float randY = rand() % 1200;
        gameObject->position = glm::vec2(randX,randY);
        cout << "Spawned at: " << randX << " " << randY << endl;
        gameObject->AddComponent(asteroidRenderComponent);
        asteroids.push_back(gameObject);
    }
}