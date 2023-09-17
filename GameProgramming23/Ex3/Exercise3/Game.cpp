#include <iostream>
#include <chrono>
#include <math.h>
#include <list>

// custom headers
#include "./Headers/Engine.h"
#include "./Headers/Player.h"
#include "./Headers/GameObject.h"

Engine *engine;
std::list<GameObject *> gameObjects;

void LongComputation();
void FixedLoop();

int main()
{
	gameObjects = {};

	Player *player = new Player();
	player->Init(20, 10);
	gameObjects.push_back(player);

	engine = new Engine();
	gameObjects.push_back(engine);

	FixedLoop();

	return 0;
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