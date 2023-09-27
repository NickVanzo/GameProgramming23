//
// Created by Nicolò Vanzo on 22/09/23.
//
#include "PlayerUpdateComponent.h"
#include "Engine/MyEngine.h"

namespace Asteroids {
    PlayerUpdateComponent::PlayerUpdateComponent(std::shared_ptr<MyEngine::GameObject> g) {
        _gameObject = g;
    }
    void PlayerUpdateComponent::Init() {}
    void PlayerUpdateComponent::Update(float deltaTime) {
        MyEngine::Engine* engine = MyEngine::Engine::GetInstance();
        glm::vec2 basePos = engine->GetScreenSize() / 2.f;
    }
}
