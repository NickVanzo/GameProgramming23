//
// Created by Nicolò Vanzo on 22/09/23.
//
#include "Engine/Component.h"
#pragma once

namespace Asteroids{
    class BulletComponentUpdate: public MyEngine::Component {
    public:

        void Update(float deltaTime);
    };
}


