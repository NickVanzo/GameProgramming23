//
// Created by Nicolò Vanzo on 25/09/23.
//
#include "Component.h"

namespace  Asteroids {
    class AsteroidRenderComponent: public MyEngine::Component {
    public:
        ~AsteroidRenderComponent();
        sre::Sprite sprite;
        void Render(sre::SpriteBatch::SpriteBatchBuilder&) override;
    };
}



