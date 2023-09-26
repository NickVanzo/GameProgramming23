//
// Created by Nicolò Vanzo on 25/09/23.
//
#include "AsteroidSpawner.h"
#include "../Asteroid/AsteroidRenderComponent.h"
#include "../Asteroid/AsteroidUpdateComponent.h"
#include "MyEngine.h"
#include "../Enums/AsteroidSpawnerPositions.h"
#include <cstdlib>
#include "../Constants/Engine.h"
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
        CheckAsteroidCollisionWithBounderies();
    }
    void AsteroidSpawner::SpawnAsteroid() {
        MyEngine::Engine* engine = MyEngine::Engine::GetInstance();
        auto gameObject = engine->CreateGameObject("asteroid");

        auto asteroidRenderComponent = std::shared_ptr<Asteroids::AsteroidRenderComponent>(new Asteroids::AsteroidRenderComponent());
        auto asteroidUpdateComponent = std::shared_ptr<Asteroids::AsteroidUpdateComponent>(new Asteroids::AsteroidUpdateComponent());

        asteroidRenderComponent->sprite = engine->GetSpriteFromAtlas("meteorBrown_big1.png");
        gameObject->rotation = rand() % 360 - 180;

        float randX = 0;
        float randY = 0;

        if(direction == LOWER) {
            //spawn only along the lower part of the screen
            randX = rand() % (int) CUSTOM_WINDOW_WIDTH;
            randY = 10;
            asteroidUpdateComponent->SetDirection(LOWER);
        } else if(direction == UPPER) {
            //spawn only along the upper part of the screen
            randY = CUSTOM_WINDOW_HEIGHT + 400;
            randX = rand() % (int) CUSTOM_WINDOW_WIDTH;
            asteroidUpdateComponent->SetDirection(UPPER);
        } else {
        }
        gameObject->position = glm::vec2(randX,randY);
        gameObject->AddComponent(asteroidRenderComponent);
        gameObject->AddComponent(asteroidUpdateComponent);
        asteroids.push_back(gameObject);
    }
    void AsteroidSpawner::CheckAsteroidCollisionWithBounderies() {
        for (auto it = asteroids.begin(); it != asteroids.end();) {
            bool isCollidingWithXBoundaries = ((*it)->position.x == CUSTOM_WINDOW_WIDTH) || ((*it)->position.x == 0);
            bool isCollidingWithYBoundaries = ((*it)->position.y == CUSTOM_WINDOW_HEIGHT) || ((*it)->position.y == 0);

            if (isCollidingWithXBoundaries || isCollidingWithYBoundaries) {
                it = asteroids.erase(it);
            } else {
                ++it;
            }
        }
    }
}