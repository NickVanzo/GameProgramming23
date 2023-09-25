//
// Created by Nicolò Vanzo on 25/09/23.
//
#include "AsteroidRenderComponent.h"
namespace Asteroids {
    using namespace std;
//    AsteroidRenderComponent::AsteroidRenderComponent() {
//        MyEngine::GameObject *parent = GetGameObject();

//    }
    void AsteroidRenderComponent::Render(sre::SpriteBatch::SpriteBatchBuilder & builder) {
        MyEngine::GameObject *parent = GetGameObject();
        sprite.setPosition(parent->position);
        sprite.setRotation(parent->rotation);
        builder.addSprite(sprite);
    }
}
