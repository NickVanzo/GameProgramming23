//
// Created by Nicolò Vanzo on 27/09/23.
//

#include "sre/SDLRenderer.hpp"
#include "sre/SpriteAtlas.hpp"

#include "Engine/MyEngine.h"
#include "../Player/PlayerUpdateComponent.h"
#include "../Player/PlayerComponentRenderer.h"
#include "../Constants/Player.h"
#include "../Enums/AsteroidSpawnerPositions.h"
#include "../../Factory/Factory.h"
GameManager::~GameManager() {
    std::cout << "Distruttore game manager" << std::endl;
}
void GameManager::StartGame() {
    CreatePlayer();
    CreateAsteroidSpawner();
}
void GameManager::CreatePlayer() {
    std::shared_ptr<Factory> factory = std::make_shared<Factory>();
    MyEngine::Engine* engine = MyEngine::Engine::GetInstance();
    std::shared_ptr<MyEngine::GameObject> gm = factory->CreateGameObject("PLAYER");
//    engine->gameObjects.push_back(gm);
}
void GameManager::CreateAsteroidSpawner() {
    MyEngine::Engine* engine = MyEngine::Engine::GetInstance();
    lowerSpawner = engine->CreateGameObject("asteroidSpawner");
    auto lowerSpawnerUpdateComponent =std::make_shared<Asteroids::AsteroidSpawner>(Asteroids::LOWER, player, lowerSpawner);
    lowerSpawner->AddComponent(lowerSpawnerUpdateComponent);

    upperSpawner = engine->CreateGameObject("asteroidSpawner");
    auto upperSpawnerUpdateComponent = std::make_shared<Asteroids::AsteroidSpawner>(Asteroids::UPPER, player, upperSpawner);
    upperSpawner->AddComponent(upperSpawnerUpdateComponent);
}