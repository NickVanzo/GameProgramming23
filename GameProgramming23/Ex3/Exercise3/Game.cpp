#include <list>
#include "./Headers/Engine.h"
#include "./Headers/Player.h"

Engine *engine;
std::list<GameObject *> gameObjects;

void Render();
void Update(float deltaTime);

int main() {
	gameObjects = {};

    engine = new Engine();
    gameObjects.push_back(engine);

	auto *player = new Player(*engine);

    engine->Init();
    return 0;
}

//void ProcessEvents(SDL_Event& event){
//    snakeSprite.setPosition(glm::vec2(pos_x_snake, pos_y_snake));
//}
