//
// Created by Nicolò Vanzo on 27/09/23.
//

#include "sre/SDLRenderer.hpp"
#include "sre/SpriteAtlas.hpp"

#include "Engine/MyEngine.h"
#include "../Player/PlayerUpdateComponent.h"
#include "../Player/PlayerComponentRenderer.h"
#include "../Player/PlayerProcessEventsComponent.h"
#include "../Constants/Player.h"
#include "../Enums/AsteroidSpawnerPositions.h"
GameManager::~GameManager() {
    std::cout << "Distruttore game manager" << std::endl;
}
void GameManager::StartGame() {
    CreatePlayer();
//    CreateAsteroidSpawner();
}
void GameManager::CreatePlayer() {
    MyEngine::Engine* engine = MyEngine::Engine::GetInstance();
    player = engine->CreateGameObject("Player");
    player->SetRadius(Asteroids::PLAYER_RADIUS);

    auto playerController = std::make_unique<Asteroids::PlayerProcessEventsComponent>(player);
    auto playerRenderer = std::make_unique<Asteroids::PlayerComponentRenderer>(player);
    auto playerProcessEventsComponent = std::make_unique<Asteroids::PlayerProcessEventsComponent>(player);
    playerRenderer->sprite = engine->atlas->get("playerShip1_blue.png");
    playerRenderer->deathSprite = engine->atlas->get("bang.png");

    player->AddComponent(std::move(playerController));
    player->AddComponent(std::move(playerRenderer));
    player->AddComponent(std::move(playerProcessEventsComponent));

}
void GameManager::CreateAsteroidSpawner() {
//    MyEngine::Engine* engine = MyEngine::Engine::GetInstance();
//    upperSpawner = engine->CreateGameObject("asteroidSpawner");
//    auto upperSpawnerUpdateComponent =std::make_shared<Asteroids::AsteroidSpawner>(Asteroids::LOWER, player, upperSpawner);
//    upperSpawner->AddComponent(upperSpawnerUpdateComponent);
}