//
// Created by Nicolò Vanzo on 22/09/23.
//
#include "sre/SDLRenderer.hpp"
#include "sre/SpriteAtlas.hpp"

#include "Engine/MyEngine.h"
#include "Game/Player/PlayerUpdateComponent.h"
#include "Game/Player/PlayerComponentRenderer.h"
#include "Game/Player/PlayerProcessEventsComponent.h"
#include "Game/AsteroidSpawner/AsteroidSpawner.h"
#include "Game/Enums/AsteroidSpawnerPositions.h"
#include "Game/Constants/Engine.h"
#include "Game/Constants/Player.h"

void InitGame();
void ProcessEvents(SDL_Event& event);
void Update(float deltaTime);
void Render();

MyEngine::Engine engine;
glm::vec2 window_size = glm::vec2(CUSTOM_WINDOW_WIDTH, CUSTOM_WINDOW_HEIGHT);
sre::SDLRenderer renderer;
sre::Camera camera;
std::shared_ptr<sre::SpriteAtlas> atlas;

int main() {
    renderer.frameRender = Render;
    renderer.frameUpdate = Update;
    renderer.keyEvent = ProcessEvents;

    renderer.setWindowSize(window_size);
    renderer.init();
    camera.setWindowCoordinates();

    engine.Init();

    auto gameObject = engine.CreateGameObject("Player");
    gameObject->SetRadius(Asteroids::PLAYER_RADIUS);

    auto playerController = std::shared_ptr<Asteroids::PlayerUpdateComponent>(new Asteroids::PlayerUpdateComponent());
    auto playerRenderer = std::make_shared<Asteroids::PlayerComponentRenderer>();
    auto playerProcessEventsComponent = std::make_shared<Asteroids::PlayerProcessEventsComponent>();
    playerRenderer->sprite = engine.GetSpriteFromAtlas("playerShip1_blue.png");
    playerRenderer->deathSprite = engine.GetSpriteFromAtlas("bang.png");
    gameObject->AddComponent(playerController);
    gameObject->AddComponent(playerRenderer);
    gameObject->AddComponent(playerProcessEventsComponent);

    auto asteroidSpawnerGameObject = engine.CreateGameObject("AsteroidSpawner");
    auto upperAsteroidSpawnerGameObject = engine.CreateGameObject("UpperAsteroidSpawner");
    auto asteroidSpawnerUpdateComponent = std::shared_ptr<Asteroids::AsteroidSpawner>(new Asteroids::AsteroidSpawner(Asteroids::ASTEROID_SPAWNER_POS::LOWER, *gameObject));

    asteroidSpawnerGameObject->AddComponent(asteroidSpawnerUpdateComponent);
//    upperAsteroidSpawnerGameObject->AddComponent(upperAsteroidSpawnerUpdateComponent);
    renderer.startEventLoop();
}

void ProcessEvents(SDL_Event& event) {
    engine.ProcessEvents(event);
}
void Update(float deltaTime) {
    engine.Update(deltaTime);
}
void Render() {
    engine.Render();
}