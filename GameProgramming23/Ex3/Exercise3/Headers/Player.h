#pragma once
#include <chrono>
#include "./Engine.h"
#include "./GameObject.h"
#include "sre/SDLRenderer.hpp"


class Player: public GameObject
{
public:
    explicit Player(std::shared_ptr<Engine> engine);
    void Init();
    void ProcessEvents(SDL_Event &event);
    void Update(float delta_time);
    void Render(sre::SpriteBatch::SpriteBatchBuilder&);
    void RemoveMeFromObserverList();
private:
    std::shared_ptr<Engine> engine_;
};