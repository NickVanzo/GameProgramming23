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
    AsteroidSpawner::AsteroidSpawner(int direction, std::weak_ptr<MyEngine::GameObject> player, std::weak_ptr<MyEngine::GameObject> parent):
    direction(direction), player_(player){
        _gameObject = parent;
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
//        MyEngine::Engine* engine = MyEngine::Engine::GetInstance();
//        auto gameObject = engine->CreateGameObject("asteroid");
//        std::weak_ptr<MyEngine::GameObject> obj = gameObject;
//        auto asteroidRenderComponent = std::weak_ptr<Asteroids::AsteroidRenderComponent>(obj);
//        auto asteroidUpdateComponent = std::make_unique<Asteroids::AsteroidUpdateComponent>(obj);
//
//        asteroidRenderComponent->sprite = engine->atlas->get("meteorBrown_big1.png");
//        gameObject->rotation = rand() % 360 - 180;
//
//        float randX = 0;
//        float randY = 0;
//
//        if(direction == LOWER) {
//            //spawn only along the lower part of the screen
//            randX = rand() % (int) CUSTOM_WINDOW_WIDTH;
//            randY = 10;
//            asteroidUpdateComponent->SetDirection(LOWER);
//        } else if(direction == UPPER) {
//            //spawn only along the upper part of the screen
//            randY = CUSTOM_WINDOW_HEIGHT + 400;
//            randX = rand() % (int) CUSTOM_WINDOW_WIDTH;
//            asteroidUpdateComponent->SetDirection(UPPER);
//        }
//        gameObject->position = glm::vec2(randX,randY);
//        gameObject->AddComponent(asteroidRenderComponent);
//        gameObject->AddComponent(asteroidUpdateComponent);
    }
    void AsteroidSpawner::CheckAsteroidCollisionWithBounderies() {
//        MyEngine::Engine* engine = MyEngine::Engine::GetInstance();
//        std::vector<std::shared_ptr<MyEngine::GameObject>> elemntsToRemove = {};
//        for (auto it = MyEngine::gameObjects.begin(); it != MyEngine::gameObjects.end();) {
//            if((*it)->GetName() == "asteroid") {
//                bool isCollidingWithXBoundaries =  ((*it)->position.x == engine->GetScreenSize().x) || ((*it)->position.x == 0);
//                bool isCollidingWithYBoundaries = ((*it)->position.y ==  engine->GetScreenSize().y) || ((*it)->position.y == 0);
//
//                if(IsCollidingWithPlayer((*it)->position.x, (*it)->position.y)) {
////                HandleCollisionWithPlayer();
//                }
//                if (isCollidingWithXBoundaries || isCollidingWithYBoundaries) {
//                    std::cout << "Found" << std::endl;
//                    elemntsToRemove.push_back(*it);
//                    ++it;
//                } else {
//                    ++it;
//                }
//            }
//        }
//        for(auto e : elemntsToRemove) {
//           std::cout << e->GetName() << std::endl;
//        }
    }
    void AsteroidSpawner::HandleCollisionWithPlayer() {
        auto components = player_.lock().get()->GetComponents();
//        DisabledPlayerRender(components);
//        DisabledPlayerMovement(components);
    }
    void AsteroidSpawner::DisabledPlayerRender(std::list< std::shared_ptr<Component>>& components) {
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
    void AsteroidSpawner::DisabledPlayerMovement(std::list< std::shared_ptr<Component>>& components) {
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
    bool AsteroidSpawner::IsCollidingWithPlayer(float asteroidPosX, float asteroidPosY) {
        if(&player_ != nullptr) {
            float distanceBetweenPlayerAndAsteroid = pow(asteroidPosY - player_.lock().get()->position.y, 2) + pow(asteroidPosX - player_.lock().get()->position.x,2);
            return distanceBetweenPlayerAndAsteroid <= pow(asteroidsRadius + player_.lock().get()->radius, 2);
        } else {
            return false;
        }
    }
}