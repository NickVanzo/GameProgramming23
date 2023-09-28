#include "PlayerProcessEventsComponent.h"

#include <memory>
#include "PlayerUpdateComponent.h"
#include "../Laser/BulletComponentRender.h"
#include "../Laser/BulletComponentUpdate.h"
#include "sre/SDLRenderer.hpp"
#include "MyEngine.h"

namespace Asteroids {
    PlayerProcessEventsComponent::PlayerProcessEventsComponent(std::weak_ptr<MyEngine::GameObject> p) {
        _gameObject = p;
        controlsEnabled = true;
    }
    void PlayerProcessEventsComponent::KeyEvent(SDL_Event& event) {
        std::cout << "controls enabled: " <<controlsEnabled<<std::endl;
            std::weak_ptr<MyEngine::GameObject> parent = GetGameObject();
            if(controlsEnabled) {
                switch (event.key.keysym.scancode) {
                    case SDL_SCANCODE_SPACE:
                        if(controlsEnabled) {
                            Shoot();
                        } else {
                            std::cout << "restart" << std::endl;
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
                        float xPos = sin * speed;
                        float yPos = cos * speed;
                        parent.lock().get()->position.x -= xPos;
                        parent.lock().get()->position.y += yPos;
                        break;
                }
            };

    }
    void PlayerProcessEventsComponent::Shoot() {
        MyEngine::Engine* engine = MyEngine::Engine::GetInstance();
        std::weak_ptr<MyEngine::GameObject> gm = GetGameObject();

        auto gameObject = engine->CreateGameObject("bullet");
        auto bulletUpdate = std::make_shared<Asteroids::BulletComponentUpdate>(gameObject);
        auto bulletRenderer = std::make_shared<Asteroids::BulletComponentRender>(gameObject);
        bulletRenderer->sprite = engine->atlas->get("laserBlue01.png");

        bulletUpdate->SetStartingPos(glm::vec2(gm.lock()->position.x, gm.lock()->position.y));
        bulletUpdate->SetRotation(gm.lock()->rotation);
        gameObject->radius = 20.0f;
        gameObject->rotation = gm.lock()->rotation;
        gameObject->AddComponent(bulletRenderer);
        gameObject->AddComponent(bulletUpdate);
    }
    void PlayerProcessEventsComponent::TriggerPlayerDeath() {
        controlsEnabled = false;
    }
}
