#include <list>
#include "./Headers/Engine.h"
#include "./Headers/Player.h"

int main() {
    Engine* engine = Engine::GetInstance();
	auto *player = new Player(*engine);
    engine->Init();
    return 0;
}

