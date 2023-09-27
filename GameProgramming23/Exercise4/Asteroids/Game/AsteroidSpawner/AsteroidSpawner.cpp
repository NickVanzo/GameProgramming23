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
    AsteroidSpawner::AsteroidSpawner(int direction, MyEngine::GameObject& player):
    direction(direction), player_(player){}
    void AsteroidSpawner::Update(float deltaTime) {
        timeCounter -= deltaTime;
        if(timeCounter < 0) {
            SpawnAsteroid();
            timeCounter = TIME_TO_SPAWN_ASTEROID;
        }
        if(!asteroids.empty()) {
            CheckAsteroidCollisionWithBounderies();
        }
    }
    void AsteroidSpawner::SpawnAsteroid() {
        MyEngine::Engine* engine = MyEngine::Engine::GetInstance();
        auto gameObject = std::shared_ptr<MyEngine::GameObject>(engine->CreateGameObject("asteroid"));

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
        }
        gameObject->position = glm::vec2(randX,randY);
        gameObject->AddComponent(asteroidRenderComponent);
        gameObject->AddComponent(asteroidUpdateComponent);
        asteroids.insert({1, gameObject});
    std::cout << "Added steroid in map: " << asteroids.size() << std::endl;
    }
    void AsteroidSpawner::CheckAsteroidCollisionWithBounderies() {
        for (auto it = asteroids.begin(); it != asteroids.end();) {
            if(asteroids.size() == 0) return;
            bool isCollidingWithXBoundaries = ((*it).second->position.x == CUSTOM_WINDOW_WIDTH) || ((*it).second->position.x == 0);
            bool isCollidingWithYBoundaries = ((*it).second->position.y == CUSTOM_WINDOW_HEIGHT) || ((*it).second->position.y == 0);

            if(IsCollidingWithPlayer((*it).second->position.x, (*it).second->position.y)) {
                HandleCollisionWithPlayer();
            } else if(IsCollidingWithLaser((*it).second->position)) {
                asteroids.erase(it->first);
                ++it;
                std::cout << "Asteroids: " << asteroids.size() << std::endl;
            } else if(isCollidingWithXBoundaries || isCollidingWithYBoundaries) {
                asteroids.erase(it->first);
                ++it;
            } else{
                ++it;
            }
        }
    }
    void AsteroidSpawner::HandleCollisionWithPlayer() {
        auto components = player_.GetComponents();
        DisabledPlayerRender(components);
        DisabledPlayerMovement(components);
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
            float distanceBetweenPlayerAndAsteroid = pow(asteroidPosY - player_.position.y, 2) + pow(asteroidPosX - player_.position.x,2);
            return distanceBetweenPlayerAndAsteroid <= pow(asteroidsRadius + player_.radius, 2);
        } else {
            return false;
        }
    }
    bool AsteroidSpawner::IsCollidingWithLaser(vec2& asteroidPos) {
        auto components = player_.GetComponents();
        auto it = components.begin();
        std::advance(it, 2);
        std::shared_ptr<Asteroids::PlayerProcessEventsComponent> playerProcessEventsComponent = std::dynamic_pointer_cast<Asteroids::PlayerProcessEventsComponent>(*it);
        if(playerProcessEventsComponent) {
            for(auto laser : playerProcessEventsComponent->GetBullets()) {
                float distanceBetweenAsteroidAndLaser = pow(asteroidPos.y - laser->position.y, 2) + pow(asteroidPos.x - laser->position.x, 2);
                if(distanceBetweenAsteroidAndLaser <= pow(asteroidsRadius + laser->radius, 2)) {
                    return true;
                }
            }
        } else {
            std::cout << "Cast non riuscito" << std::endl;
        }
        return false;
    }
}