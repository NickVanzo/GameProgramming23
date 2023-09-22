#include <list>
#include "./Headers/Engine.h"
#include "./Headers/Player.h"
#include "./Headers/Map.h"

int main() {
    Engine* engine = Engine::GetInstance();
	auto *player = new Player(*engine);
    auto *map = new Map(*engine, *player);
    engine->Init();
    return 0;
}

