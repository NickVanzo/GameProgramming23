#include <memory>
#include "./Headers/Engine.h"
#include "./Headers/GameManager.h"

int main() {
    Engine* engine = Engine::GetInstance();
    std::shared_ptr<Asteroids::GameManager> gm = std::shared_ptr<Asteroids::GameManager>();
    gm->StartGame();
    engine->Init();
    return 0;
}

