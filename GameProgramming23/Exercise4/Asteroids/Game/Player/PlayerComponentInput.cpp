//
// Created by Nicolò Vanzo on 22/09/23.
//
#include "PlayerComponentInput.h"
#include "Engine/MyEngine.h"

namespace Asteroids {
    void PlayerComponentInput::Init() {}
    void PlayerComponentInput::Update(float deltaTime) {
        MyEngine::Engine* engine = MyEngine::Engine::GetInstance();
        MyEngine::GameObject* parent = GetGameObject();
        glm::vec2 basePos = engine->GetScreenSize() / 2.f;

        parent->position = basePos;
    }
}
