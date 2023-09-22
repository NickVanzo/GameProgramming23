//
// Created by Nicolò Vanzo on 22/09/23.
//
#include "PlayerComponentRenderer.h"
namespace Asteroids {
    void PlayerComponentRenderer::Render(sre::SpriteBatch::SpriteBatchBuilder & builder) {
        MyEngine::GameObject* parent = GetGameObject();
        sprite.setPosition(parent->position);
        sprite.setRotation(parent->rotation);
        builder.addSprite(sprite);
    }
}
