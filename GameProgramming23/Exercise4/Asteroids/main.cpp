//
// Created by Nicolò Vanzo on 22/09/23.
//
#include "sre/SDLRenderer.hpp"
#include "sre/SpriteAtlas.hpp"

#include "Engine/MyEngine.h"
#include "Game/Player/PlayerUpdateComponent.h"
#include "Game/Player/PlayerComponentRenderer.h"
#include "Game/Player/PlayerProcessEventsComponent.h"

void InitGame();
void ProcessEvents(SDL_Event& event);
void Update(float deltaTime);
void Render();

MyEngine::Engine engine;
glm::vec2 window_size = glm::vec2(800, 600);
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

    atlas = sre::SpriteAtlas::create("data/asteroids_sprites.json", "data/asteroids_sprites.png");

    auto gameObject = engine.CreateGameObject("Player");

    auto playerController = std::shared_ptr<Asteroids::PlayerUpdateComponent>(new Asteroids::PlayerUpdateComponent());
    auto playerRenderer = std::make_shared<Asteroids::PlayerComponentRenderer>();
    auto playerProcessEventsComponent = std::make_shared<Asteroids::PlayerProcessEventsComponent>();
    playerRenderer->sprite = atlas->get("playerShip1_blue.png");

    gameObject->AddComponent(playerController);
    gameObject->AddComponent(playerRenderer);
    gameObject->AddComponent(playerProcessEventsComponent);

    engine.Init();
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