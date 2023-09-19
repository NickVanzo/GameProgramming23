#pragma once
#include "GameObject.h"
#include "sre/SDLRenderer.hpp"
#include "Engine.h"

class Map: public GameObject
{
private:
    Engine &engine_;
public:
    glm::vec2 foodPosition = glm::vec2(this->engine_.window_size / 2.0f);
    explicit Map(Engine &engine);
    void Init() override;
    void ProcessEvents(SDL_Event &event) override;
    void Update(float delta_time) override;
    void Render() override;
};
