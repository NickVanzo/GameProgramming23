#pragma once
#include "sre/SDLRenderer.hpp"

class GameObject
{
private:
public:
    int pos_x;
    int pos_y;
    virtual void Init() = 0;
    virtual void Update(float delta_time) = 0;
    virtual void ProcessEvents(SDL_Event &event) = 0;
    virtual void Render() = 0;
};