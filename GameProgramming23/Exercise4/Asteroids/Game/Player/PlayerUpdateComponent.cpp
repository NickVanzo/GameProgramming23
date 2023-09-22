//
// Created by Nicolò Vanzo on 22/09/23.
//
#include "PlayerUpdateComponent.h"
#include "Engine/MyEngine.h"

namespace Asteroids {
    void PlayerUpdateComponent::Init() {}
    void PlayerUpdateComponent::Update(float deltaTime) {
        MyEngine::Engine* engine = MyEngine::Engine::GetInstance();
        MyEngine::GameObject* parent = GetGameObject();
        glm::vec2 basePos = engine->GetScreenSize() / 2.f;
        
    }
}
