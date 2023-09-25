//
// Created by Nicolò Vanzo on 25/09/23.
//
#include "AsteroidSpawner.h"
#include "../Asteroid/AsteroidRenderComponent.h"
#include "../Asteroid/AsteroidUpdateComponent.h"
#include "MyEngine.h"
#include <cstdlib>

namespace Asteroids {
    using namespace glm;
    using namespace std;
    AsteroidSpawner::AsteroidSpawner(int direction) {
        this->direction = direction;
    }
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
        auto asteroidUpdateComponent = std::shared_ptr<Asteroids::AsteroidUpdateComponent>(new Asteroids::AsteroidUpdateComponent());

        asteroidRenderComponent->sprite = engine->GetSpriteFromAtlas("meteorBrown_big1.png");
        gameObject->rotation = (rand() % 360) - 180;

        if(direction == 0) {
            //spawn only along the lower part of the screen
            float randX = rand() % 1200;
            float randY = 10;
            gameObject->position = glm::vec2(randX,randY);
            asteroidUpdateComponent->SetDirection(0);
        } else {
            //spawn only along the upper part of the screen
            float randY = 900;
            float randX = rand() % 1200;
            gameObject->position = glm::vec2(randX,randY);
            asteroidUpdateComponent->SetDirection(1);
        }

        gameObject->AddComponent(asteroidRenderComponent);
        gameObject->AddComponent(asteroidUpdateComponent);
        asteroids.push_back(gameObject);
    }
}