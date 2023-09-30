//
// Created by Nicolò Vanzo on 22/09/23.
//
#include "Engine/Component.h"
#ifndef SIMPLERENDERENGINEPROJECT_PLAYERCOMPONENTRENDERER_H
#define SIMPLERENDERENGINEPROJECT_PLAYERCOMPONENTRENDERER_H
namespace Asteroids {
    class PlayerComponentRenderer: public MyEngine::Component {
    public:
        PlayerComponentRenderer(std::weak_ptr<MyEngine::GameObject>);
        sre::Sprite sprite;
        sre::Sprite deathSprite;

        void Render(sre::SpriteBatch::SpriteBatchBuilder&) override;
        void TriggerPlayerDeath();
    };
}
#endif //SIMPLERENDERENGINEPROJECT_PLAYERCOMPONENTRENDERER_H
