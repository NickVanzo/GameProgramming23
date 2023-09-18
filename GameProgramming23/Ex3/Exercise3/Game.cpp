#include <list>
#include "./Headers/Engine.h"
#include "./Headers/Player.h"

Engine *engine;

int main() {
    engine = new Engine();
	auto *player = new Player(*engine);

    engine->Init();
    return 0;
}

