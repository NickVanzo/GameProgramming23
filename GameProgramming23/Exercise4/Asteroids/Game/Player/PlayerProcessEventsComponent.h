//
// Created by Nicolò Vanzo on 22/09/23.
//
#include "Engine/Component.h"

#pragma once
namespace Asteroids {
class PlayerProcessEventsComponent: public MyEngine::Component {
public:
    PlayerProcessEventsComponent(std::shared_ptr<MyEngine::GameObject>);
    bool controlsEnabled = true;
    void KeyEvent(SDL_Event&) override;
    void TriggerPlayerDeath();
private:
    void Shoot();
};
}



