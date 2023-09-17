#include <iostream>
#include <chrono>
#include <math.h>
#include <list>

// custom headers
#include "./Headers/Engine.h"
#include "./Headers/Player.h"
#include "./Headers/GameObject.h"

#include "sre/SDLRenderer.hpp"
#include "sre/SpriteAtlas.hpp"

glm::vec2 window_size = glm::vec2(800, 600);
glm::vec2 initial_position_snake = glm::vec2(400, 400);
sre::SDLRenderer renderer;
sre::Camera camera;
std::shared_ptr<sre::SpriteAtlas> atlas;
sre::Sprite sprite;
sre::Sprite snakeSprite;

Engine *engine;
std::list<GameObject *> gameObjects;

void LongComputation();
void FixedLoop();
void Render();
void Update(float deltaTime);
void ProcessEvents(SDL_Event& event) {}

int main() {
//	gameObjects = {};
//
//	Player *player = new Player();
//	player->Init(20, 10);
//	gameObjects.push_back(player);
//
//	engine = new Engine();
//	gameObjects.push_back(engine);

//	FixedLoop();

    renderer.frameRender = Render;
    renderer.frameUpdate = Update;
    renderer.keyEvent = ProcessEvents;
    renderer.setWindowSize(window_size);
    renderer.init();
    camera.setWindowCoordinates();
    atlas = sre::SpriteAtlas::create("data/snake.json",
                                     "data/snake.png");
    snakeSprite = atlas->get("snake-body.png");
    snakeSprite.setPosition(initial_position_snake);
    sprite = atlas->get("berry.png");
    sprite.setPosition(window_size / 2.0f);
    renderer.startEventLoop();

    return 0;
}

void Update(float deltaTime) {

}

void Render() {
    sre::RenderPass renderPass = sre::RenderPass::create()
            .withCamera(camera)
            .withClearColor(true, { .3f, .3f, 1, 1 })
            .build();
    sre::SpriteBatch::SpriteBatchBuilder spriteBatchBuilder
            = sre::SpriteBatch::create();
    // send spriteBatchBuilder to your game elements, so that they can add their sprites for rendering
    spriteBatchBuilder.addSprite(sprite);
    spriteBatchBuilder.addSprite(snakeSprite);
    auto spriteBatch = spriteBatchBuilder.build();
    renderPass.draw(spriteBatch);
}

void FixedLoop()
{
	while (true)
	{
		engine->time_start = std::chrono::steady_clock::now();

		LongComputation();

		for (GameObject *obj : gameObjects)
			obj->Update();

		for (GameObject *obj : gameObjects)
			obj->ProcessEvents();

		for (GameObject *obj : gameObjects)
			obj->Render();

		engine->time_end_computation = std::chrono::steady_clock::now();
		std::chrono::duration<double> sleep_time = engine->target_frame_time - engine->GetTimeComputationMs();



		engine->time_elapsed = std::chrono::steady_clock::now() - engine->time_start;
	}
}

void LongComputation()
{
	// get a random number between 0.01 and 0.016
	double sleep_time = (10 + std::rand() % 6) / 1000.0;
}