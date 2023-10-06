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
        glm::vec3 positionFromMatrix = parent.lock()->transform[3];
        sprite.setPosition(positionFromMatrix);
        sprite.setRotation(parent.lock()->rotation);
        builder.addSprite(sprite);
    }
    void PlayerComponentRenderer::TriggerPlayerDeath() {
        sprite = deathSprite;
    }


//    void PlayerComponentRenderer::SetDeathSprite(sre::Sprite sprite) {
//        deathSprite = sprite;
//    }
}
