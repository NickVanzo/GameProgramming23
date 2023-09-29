//
// Created by Nicolò Vanzo on 22/09/23.
//
#include "PlayerUpdateComponent.h"
#include "Engine/MyEngine.h"
#include "../Laser/BulletComponentRender.h"
#include "../Laser/BulletComponentUpdate.h"

namespace Asteroids {
    PlayerUpdateComponent::PlayerUpdateComponent(std::weak_ptr<MyEngine::GameObject> g) {
        MyEngine::Engine* engine = MyEngine::Engine::GetInstance();
        _gameObject = g;
        _gameObject.lock()->position = engine->GetScreenSize() / 2.f;
    }
    void PlayerUpdateComponent::Init() {}
    void PlayerUpdateComponent::Update(float deltaTime) {}
    void PlayerUpdateComponent::KeyEvent(SDL_Event & event) {
        std::weak_ptr<MyEngine::GameObject> parent = GetGameObject();
        switch (event.key.keysym.scancode) {
            case SDL_SCANCODE_SPACE:
                if(controlsEnabled) {
                    Shoot();
                } else {
                    MyEngine::Engine::GetInstance()->RestartGame();
                };
                break;
            case SDL_SCANCODE_D:
                parent.lock().get()->rotation -= 10;
                break;
            case SDL_SCANCODE_A:
                parent.lock().get()->rotation += 10;
                break;
            case SDL_SCANCODE_W:
                float speed = 50;
                float sin = glm::sin(glm::radians(parent.lock().get()->rotation));
                float cos = glm::cos(glm::radians(parent.lock().get()->rotation));
                float xPos = sin * speed * controlsEnabled;
                float yPos = cos * speed * controlsEnabled;
                parent.lock().get()->position.x -= xPos;
                parent.lock().get()->position.y += yPos;
                break;
        }
    }
    void PlayerUpdateComponent::Shoot() {
        MyEngine::Engine* engine = MyEngine::Engine::GetInstance();
        std::weak_ptr<MyEngine::GameObject> gm = GetGameObject();

        auto gameObject = engine->CreateGameObject("bullet");
        auto bulletUpdate = std::make_shared<Asteroids::BulletComponentUpdate>(gameObject);
        auto bulletRenderer = std::make_shared<Asteroids::BulletComponentRender>(gameObject);
        bulletRenderer->sprite = engine->atlas->get("laserBlue01.png");

        bulletUpdate->SetStartingPos(glm::vec2(gm.lock()->position.x, gm.lock()->position.y));
        bulletUpdate->SetRotation(gm.lock()->rotation);
        gameObject->radius = 5.0f;
        gameObject->rotation = gm.lock()->rotation;
        gameObject->AddComponent(bulletRenderer);
        gameObject->AddComponent(bulletUpdate);
    }
    void PlayerUpdateComponent::TriggerPlayerDeath() {
        controlsEnabled = false;
    }
}
