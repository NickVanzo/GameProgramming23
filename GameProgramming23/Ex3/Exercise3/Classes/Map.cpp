#include "../Headers/Map.h"
#include "sre/SDLRenderer.hpp"
#include <cstdlib>

Map::Map(Engine &engine, Player &player): engine_(engine), player_(player) {
    this->engine_.Attach(this);
}
void Map::Init() {}
void Map::Update(float delta_time) {
    if(PlayerCollidedWithFood()) {
        int newPosX = rand() % (int) this->engine_.window_size.x  + 1; // NOLINT(*-msc50-cpp)
        int newPosY = rand() % (int) this->engine_.window_size.y + 1; // NOLINT(*-msc50-cpp)
        foodPosition = glm::vec2(newPosX,newPosY);
    }
}

void Map::ProcessEvents(SDL_Event &event) {}
void Map::Render() {
    this->engine_.sprite.setPosition(foodPosition);
}
bool Map::PlayerCollidedWithFood() const {
    glm::vec2 foodPos = this->engine_.sprite.getPosition();
    int dx = player_.x_pos - (int) foodPos.x;
    int dy = player_.y_pos - (int) foodPos.y;
    double distance = std::sqrt(dx * dx + dy * dy);
    return distance <= 10;
}
