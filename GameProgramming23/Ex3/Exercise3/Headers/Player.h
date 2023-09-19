#pragma once
#include <chrono>
#include "./Engine.h"
#include "./GameObject.h"
#include "sre/SDLRenderer.hpp"

class Player: public GameObject
{
public:
    explicit Player(Engine &engine);
    int x_pos = 20;
    int y_pos = 10;
    char direction;
    void Init() override;
    void ProcessEvents(SDL_Event &event) override;
    void Update(float delta_time) override;
    void Render() override;
    void RemoveMeFromObserverList();
private:
    Engine &engine_;
    enum directions_ {SUD = 's', NORD = 'n', EST = 'e', OVEST = 'o'};
    void MovePlayer();
    void ChangeDirectionIfPlayerMoves(SDL_Event &event);
};