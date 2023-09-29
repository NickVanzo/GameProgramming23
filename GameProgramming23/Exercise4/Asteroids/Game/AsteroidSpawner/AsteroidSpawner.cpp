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
#include "../Player/PlayerComponentRenderer.h"
#include "../Player/PlayerUpdateComponent.h"
namespace Asteroids {
    using namespace glm;
    using namespace std;
    AsteroidSpawner::AsteroidSpawner(int direction, std::shared_ptr<MyEngine::GameObject> player, std::weak_ptr<MyEngine::GameObject> parent):
    direction(direction), player(player){
        _gameObject = parent;
    }
    void AsteroidSpawner::Update(float deltaTime) {
        timeCounter -= deltaTime;
        if(timeCounter < 0) {
            SpawnAsteroid();
            timeCounter = TIME_TO_SPAWN_ASTEROID;
        }
        auto objectsToRemove = CheckAsteroidCollisionWithBounderiesOrPlayer();

        if(!objectsToRemove.empty()) {
            for(const auto & i : objectsToRemove) {
                MyEngine::Engine::GetInstance()->RemoveObject(i);
            }
        }

        auto objectsCollidingWithLasers = ChecksAsteroidCollisionsWithLasers();
        if(!objectsCollidingWithLasers.empty()) {
            for(const auto & i : objectsCollidingWithLasers) {
                MyEngine::Engine::GetInstance()->RemoveObject(i);
            }
        }
    }
    void AsteroidSpawner::SpawnAsteroid() {
        MyEngine::Engine* engine = MyEngine::Engine::GetInstance();
        auto gameObject = engine->CreateGameObject("asteroid");
        std::weak_ptr<MyEngine::GameObject> obj = gameObject;
        auto asteroidRenderComponent = std::make_shared<Asteroids::AsteroidRenderComponent>(obj);
        auto asteroidUpdateComponent = std::make_shared<Asteroids::AsteroidUpdateComponent>(obj);

        asteroidRenderComponent->sprite = engine->atlas->get("meteorBrown_big1.png");
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
        }
        gameObject->position = glm::vec2(randX,randY);
        gameObject->AddComponent(asteroidRenderComponent);
        gameObject->AddComponent(asteroidUpdateComponent);

    }

    std::vector<std::shared_ptr<MyEngine::GameObject>> AsteroidSpawner::ChecksAsteroidCollisionsWithLasers() {
        MyEngine::Engine* engine = MyEngine::Engine::GetInstance();
        std::vector<std::shared_ptr<MyEngine::GameObject>> objectsToRemove = {};
        auto gameManager = engine->GetGameManager();
        for(int i = 0; i < engine->gameObjects.size(); i++) {
            auto asteroidGameObject = engine->gameObjects[i];
            if(asteroidGameObject == nullptr) continue;
            if(asteroidGameObject->GetName() == "asteroid") {
                for(int j = 0; j < engine->gameObjects.size(); j++) {
                    if(engine->gameObjects[j]->GetName() == "bullet") {
                        auto bulletGameObject = engine->gameObjects[j];
                        float distanceBetweenLaserAndAsteroid = pow(asteroidGameObject->position.y - bulletGameObject->position.y, 2) + pow(asteroidGameObject->position.x - bulletGameObject->position.x, 2);
                        bool areTwoObjectsColliding = distanceBetweenLaserAndAsteroid <= pow(asteroidsRadius + bulletGameObject->radius, 2);
                        if(areTwoObjectsColliding) {
                            gameManager->points++;
                            std::cout << gameManager->points << std::endl;
                            objectsToRemove.push_back(bulletGameObject);
                            objectsToRemove.push_back(asteroidGameObject);
                        }
                        if(!areTwoObjectsColliding && bulletGameObject->timeAlive > 1) {
                            objectsToRemove.push_back(bulletGameObject);
                        }
                    }
                }
            }
        }
        return objectsToRemove;
    }

    std::vector<std::shared_ptr<MyEngine::GameObject>> AsteroidSpawner::CheckAsteroidCollisionWithBounderiesOrPlayer() {
        MyEngine::Engine* engine = MyEngine::Engine::GetInstance();
        std::vector<std::shared_ptr<MyEngine::GameObject>> objectsToRemove = {};
        for(int i = 0; i < engine->gameObjects.size(); ++i) {
            auto gameObject = engine->gameObjects[i];
            if(gameObject== nullptr) continue;
            if(gameObject->GetName() == "asteroid") {
                bool isCollidingWithXBoundaries = (gameObject->position.x >= engine->GetScreenSize().x) || (gameObject->position.x == 0);
                bool isCollidingWithYBoundaries = (gameObject->position.y >=  engine->GetScreenSize().y) || (gameObject->position.y == 0);

                if(isCollidingWithYBoundaries || isCollidingWithXBoundaries) {
                    objectsToRemove.push_back(gameObject);
                }
                if(IsCollidingWithPlayer(gameObject->position.x, gameObject->position.y)) {
                    HandleCollisionWithPlayer();
                }
            }
        }
        return objectsToRemove;
    }

    bool AsteroidSpawner::IsCollidingWithPlayer(float asteroidPosX, float asteroidPosY) {
        if(player != nullptr) {
            float distanceBetweenPlayerAndAsteroid = pow(asteroidPosY - player->position.y, 2) + pow(asteroidPosX - player->position.x,2);
            return distanceBetweenPlayerAndAsteroid <= pow(asteroidsRadius + player->radius, 2);
        } else {
            return false;
        }
    }
    void AsteroidSpawner::HandleCollisionWithPlayer() {
        auto components = player->GetComponents();
        DisabledPlayerRender(components);
        DisabledPlayerMovement(components);
    }
    void AsteroidSpawner::DisabledPlayerRender(std::vector< std::shared_ptr<Component>>& components) {
        auto it = components.begin();
        // the process events component has index 0 by "business logic", an hashmap would be better to store the components
        // the render component has index 1 by "business logic", an hashmap would be better to store the components
        std::advance(it, 1);
        std::shared_ptr<Asteroids::PlayerComponentRenderer> playerRenderComponent = std::dynamic_pointer_cast<Asteroids::PlayerComponentRenderer>(*it);
        if(playerRenderComponent) {
            playerRenderComponent->TriggerPlayerDeath();
        } else {
            std::cout << "Cast non riuscito" << std::endl;
        }
    }
    void AsteroidSpawner::DisabledPlayerMovement(std::vector< std::shared_ptr<Component>>& components) {
        auto it = components.begin();
        std::advance(it, 0);
        std::shared_ptr<Asteroids::PlayerUpdateComponent> playerComponent = std::dynamic_pointer_cast<Asteroids::PlayerUpdateComponent>(*it);
        if(playerComponent) {
            playerComponent->TriggerPlayerDeath();
        } else {
            std::cout << "Cast non riuscito" << std::endl;
        }
    }

}