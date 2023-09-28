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
#include "../Player/PlayerProcessEventsComponent.h"
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
        auto objectsToRemove = CheckAsteroidCollisionWithBounderies();
        if(!objectsToRemove.empty()) {
            for(const auto & i : objectsToRemove) {
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

    std::vector<std::shared_ptr<MyEngine::GameObject>> AsteroidSpawner::CheckAsteroidCollisionWithBounderies() {
        MyEngine::Engine* engine = MyEngine::Engine::GetInstance();
        std::vector<std::shared_ptr<MyEngine::GameObject>> objectsToRemove = {};
        for(int i = 0; i < engine->gameObjects.size(); ++i) {
            auto gameObject = engine->gameObjects[i];
            if(gameObject== nullptr) continue;
            if(gameObject->GetName() == "asteroid") {
                bool isCollidingWithXBoundaries = (gameObject->position.x >= engine->GetScreenSize().x) || (gameObject->position.x == 0);
                bool isCollidingWithYBoundaries = (gameObject->position.y >=  engine->GetScreenSize().y) || (gameObject->position.y == 0);
                auto lasers = IsCollidingWithLasers(gameObject->position);
                for(auto l : lasers) {
                    objectsToRemove.push_back(l);
                }
                if(!lasers.empty()) {
                    objectsToRemove.push_back(gameObject);
                }
                if(isCollidingWithYBoundaries || isCollidingWithXBoundaries) {
                    objectsToRemove.push_back(gameObject);
                }
//
                if(IsCollidingWithPlayer(gameObject->position.x, gameObject->position.y)) {
                    HandleCollisionWithPlayer();
                }
            }
        }
        return objectsToRemove;
    }
    std::vector<std::shared_ptr<MyEngine::GameObject>> AsteroidSpawner::IsCollidingWithLasers(glm::vec2 asteroidPos) {
        MyEngine::Engine* engine =MyEngine::Engine::GetInstance();
      auto gameObjects = engine->gameObjects;
      std::vector<std::shared_ptr<MyEngine::GameObject>> objsToRemove = {};
      for(int i = 0; i < gameObjects.size(); i++) {
          if(gameObjects[i]->GetName() == "bullet") {
              auto gameObject = gameObjects[i];
              float distanceBetweenLaserAndAsteroid = pow(asteroidPos.y - gameObject->position.y, 2) + pow(asteroidPos.x - gameObject->position.x, 2);
              if(distanceBetweenLaserAndAsteroid <= pow(asteroidsRadius + gameObject->radius, 2) || gameObject->timeAlive > 1) {
                  objsToRemove.push_back(gameObject);
              }
          }
      }
      return objsToRemove;
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
        // the process events component has index 2 by "business logic", an hashmap would be better to store the components
        std::advance(it, 2);
        std::shared_ptr<Asteroids::PlayerProcessEventsComponent> playerProcessEventsComponent = std::dynamic_pointer_cast<Asteroids::PlayerProcessEventsComponent>(*it);
        if(playerProcessEventsComponent) {
            playerProcessEventsComponent->TriggerPlayerDeath();
        } else {
            std::cout << "Cast non riuscito" << std::endl;
        }
    }
    void AsteroidSpawner::DisabledPlayerMovement(std::vector< std::shared_ptr<Component>>& components) {
        auto it = components.begin();
        // the render component has index 1 by "business logic", an hashmap would be better to store the components
        std::advance(it, 1);
        std::shared_ptr<Asteroids::PlayerComponentRenderer> playerRenderComponent = std::dynamic_pointer_cast<Asteroids::PlayerComponentRenderer>(*it);
        if(playerRenderComponent) {
            playerRenderComponent->TriggerPlayerDeath();
        } else {
            std::cout << "Cast non riuscito" << std::endl;
        }
    }

}