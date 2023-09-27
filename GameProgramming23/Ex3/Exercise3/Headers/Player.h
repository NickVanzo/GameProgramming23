#pragma once
#include <chrono>
#include "./Engine.h"
#include "./GameObject.h"
#include "sre/SDLRenderer.hpp"
namespace Asteroids {
    class Player: public GameObject
    {
    public:
        Player(sre::Sprite);
        ~Player();
        void Init();
        void ProcessEvents(SDL_Event &event);
        void Update(float delta_time);
        void Render(sre::SpriteBatch::SpriteBatchBuilder&);
        void RemoveMeFromObserverList();
    private:
        std::shared_ptr<Engine> engine_;
        sre::Sprite sprite_;
    };
}
