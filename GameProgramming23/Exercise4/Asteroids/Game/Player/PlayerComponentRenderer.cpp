//
// Created by Nicolò Vanzo on 22/09/23.
//
#include "PlayerComponentRenderer.h"
namespace Asteroids {
    PlayerComponentRenderer::PlayerComponentRenderer(std::weak_ptr<MyEngine::GameObject> g) {
        _gameObject = g;
    }
    void PlayerComponentRenderer::Render(sre::SpriteBatch::SpriteBatchBuilder & builder) {
        std::weak_ptr<MyEngine::GameObject> parent = GetGameObject();
        sprite.setPosition(parent.lock().get()->position);
        sprite.setRotation(parent.lock().get()->rotation);
        builder.addSprite(sprite);
    }
    void PlayerComponentRenderer::TriggerPlayerDeath() {
        sprite = deathSprite;
    }


//    void PlayerComponentRenderer::SetDeathSprite(sre::Sprite sprite) {
//        deathSprite = sprite;
//    }
}
