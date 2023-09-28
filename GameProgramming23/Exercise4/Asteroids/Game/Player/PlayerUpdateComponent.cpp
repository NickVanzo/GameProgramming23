//
// Created by Nicolò Vanzo on 22/09/23.
//
#include "PlayerUpdateComponent.h"
#include "Engine/MyEngine.h"

namespace Asteroids {
    PlayerUpdateComponent::PlayerUpdateComponent(std::weak_ptr<MyEngine::GameObject> g) {
        MyEngine::Engine* engine = MyEngine::Engine::GetInstance();
        _gameObject = g;
        _gameObject.lock()->position = engine->GetScreenSize() / 2.f;
    }
    void PlayerUpdateComponent::Init() {

    }
    void PlayerUpdateComponent::Update(float deltaTime) {
    }
}
