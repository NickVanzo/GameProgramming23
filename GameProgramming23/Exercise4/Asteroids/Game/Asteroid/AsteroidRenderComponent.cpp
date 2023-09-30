//
// Created by Nicolò Vanzo on 25/09/23.
//
#include "AsteroidRenderComponent.h"
namespace Asteroids {
    using namespace std;
    AsteroidRenderComponent::AsteroidRenderComponent(std::weak_ptr<MyEngine::GameObject> p) {
        _gameObject = p;
    }
    void AsteroidRenderComponent::Render(sre::SpriteBatch::SpriteBatchBuilder & builder) {
        std::weak_ptr<MyEngine::GameObject> parent = GetGameObject();
        sprite.setPosition(parent.lock().get()->position);
        sprite.setRotation(parent.lock().get()->rotation);
        builder.addSprite(sprite);
    }
}
