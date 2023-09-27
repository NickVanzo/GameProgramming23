#include <list>
#include "./Headers/Engine.h"
#include "./Headers/Player.h"
#include "./Headers/Asteroids.h"
int main() {
    Engine* engine = Engine::GetInstance();
    std::cout << "Objects: " << Asteroids::gameObjects.size() << std::endl;
//	auto *player = new Player(*engine);
    engine->Init();
    return 0;
}

