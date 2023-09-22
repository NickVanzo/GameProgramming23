#pragma once
#include "GameObject.h"
#include "sre/SDLRenderer.hpp"
#include "Engine.h"
#include "Player.h"

class Map: public GameObject
{
private:
    Engine &engine_;
    Player &player_;
    int points;
    int deaths;
public:
    glm::vec2 foodPosition = glm::vec2(this->engine_.window_size / 2.0f);
    explicit Map(Engine &engine, Player &player);
    void Init() override;
    void ProcessEvents(SDL_Event &event) override;
    void Update(float delta_time) override;
    void Render() override;
    bool PlayerCollidedWithFood() const;
    void AddPoint();
    void AddDeath();
};
