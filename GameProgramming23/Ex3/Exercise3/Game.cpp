#include <list>
#include "./Headers/Engine.h"
#include "./Headers/Player.h"

Engine *engine;
std::list<GameObject *> gameObjects;

int main() {
	gameObjects = {};

    engine = new Engine();
    gameObjects.push_back(engine);

	auto *player = new Player(*engine);

    engine->Init();
    return 0;
}

