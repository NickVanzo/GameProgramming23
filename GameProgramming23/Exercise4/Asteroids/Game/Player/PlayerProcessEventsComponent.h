//
// Created by Nicolò Vanzo on 22/09/23.
//
#include "Engine/Component.h"

#pragma once
namespace Asteroids {
class PlayerProcessEventsComponent: public MyEngine::Component {
public:
    PlayerProcessEventsComponent(std::weak_ptr<MyEngine::GameObject>);
    bool controlsEnabled;
    void KeyEvent(SDL_Event&) override;
    void TriggerPlayerDeath();
private:
    void Shoot();
};
}



