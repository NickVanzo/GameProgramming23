//
// Created by Nicolò Vanzo on 22/09/23.
//
#include "Engine/Component.h"

#pragma once
namespace Asteroids {
class PlayerProcessEventsComponent: public MyEngine::Component {
public:
    bool controlsEnabled = true;
    void KeyEvent(SDL_Event&) override;
    void TriggerPlayerDeath();
    std::list<MyEngine::GameObject*> GetBullets();
private:
    std::list<MyEngine::GameObject*> bullets = {};
    void Shoot();
};
}



