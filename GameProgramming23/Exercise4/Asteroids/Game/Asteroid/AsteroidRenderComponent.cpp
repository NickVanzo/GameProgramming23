//
// Created by Nicolò Vanzo on 25/09/23.
//
#include "AsteroidRenderComponent.h"
namespace Asteroids {
    using namespace std;
    AsteroidRenderComponent::AsteroidRenderComponent(std::shared_ptr<MyEngine::GameObject> p) {
        _gameObject = p;
    }
    void AsteroidRenderComponent::Render(sre::SpriteBatch::SpriteBatchBuilder & builder) {
        std::shared_ptr<MyEngine::GameObject> parent = GetGameObject();
        sprite.setPosition(parent->position);
        sprite.setRotation(parent->rotation);
        builder.addSprite(sprite);
    }
}
