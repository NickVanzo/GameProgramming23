#include "../Headers/Map.h"
#include "sre/SDLRenderer.hpp"

Map::Map(Engine &engine): engine_(engine) {
    this->engine_.Attach(this);
}
void Map::Init() {}
void Map::Update(float delta_time) {}
void Map::ProcessEvents(SDL_Event &event) {}
void Map::Render() {
    this->engine_.sprite.setPosition(this->engine_.window_size / 2.0f);
}
