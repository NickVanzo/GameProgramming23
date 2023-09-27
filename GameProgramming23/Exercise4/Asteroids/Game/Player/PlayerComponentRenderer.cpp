//
// Created by Nicolò Vanzo on 22/09/23.
//
#include "PlayerComponentRenderer.h"
namespace Asteroids {
    PlayerComponentRenderer::PlayerComponentRenderer(std::shared_ptr<MyEngine::GameObject> g) {
        _gameObject = g;
    }
    void PlayerComponentRenderer::Render(sre::SpriteBatch::SpriteBatchBuilder & builder) {
        std::shared_ptr<MyEngine::GameObject> parent = GetGameObject();
        sprite.setPosition(parent->position);
        sprite.setRotation(parent->rotation);
        builder.addSprite(sprite);
    }
    void PlayerComponentRenderer::TriggerPlayerDeath() {
        sprite = deathSprite;
    }


//    void PlayerComponentRenderer::SetDeathSprite(sre::Sprite sprite) {
//        deathSprite = sprite;
//    }
}
