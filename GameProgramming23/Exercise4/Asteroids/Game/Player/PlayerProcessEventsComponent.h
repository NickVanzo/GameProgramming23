//
// Created by Nicolò Vanzo on 22/09/23.
//
#include "Engine/Component.h"

#pragma once
namespace Asteroids {
class PlayerProcessEventsComponent: public MyEngine::Component {
public:
        void KeyEvent(SDL_Event&) override;
private:
    void Shoot();
    };
}



