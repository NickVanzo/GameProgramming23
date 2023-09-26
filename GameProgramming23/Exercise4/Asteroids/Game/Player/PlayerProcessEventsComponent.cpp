#include "PlayerProcessEventsComponent.h"
#include "PlayerUpdateComponent.h"
#include "../Laser/BulletComponentRender.h"
#include "../Laser/BulletComponentUpdate.h"
#include "sre/SDLRenderer.hpp"
#include "MyEngine.h"

namespace Asteroids {
    void PlayerProcessEventsComponent::KeyEvent(SDL_Event& event) {
        if(controlsEnabled) {
            MyEngine::GameObject* parent = GetGameObject();
            switch (event.key.keysym.scancode) {
                case SDL_SCANCODE_SPACE:
                    Shoot();
                    break;
                case SDL_SCANCODE_D:
                    parent->rotation -= 10;
                    break;
                case SDL_SCANCODE_A:
                    parent->rotation += 10;
                    break;
                case SDL_SCANCODE_W:
                    float speed = 50;
                    float sin = glm::sin(glm::radians(parent->rotation));
                    float cos = glm::cos(glm::radians(parent->rotation));
                    float xPos = sin * speed;
                    float yPos = cos * speed;
                    parent->position.x -= xPos;
                    parent->position.y += yPos;
                    break;
            }
        }
    }
    void PlayerProcessEventsComponent::Shoot() {
        MyEngine::Engine* engine = MyEngine::Engine::GetInstance();
        MyEngine::GameObject* gm = GetGameObject();

        auto gameObject = engine->CreateGameObject("bullet");
        auto bulletUpdate = std::shared_ptr<Asteroids::BulletComponentUpdate>(new Asteroids::BulletComponentUpdate());
        auto bulletRenderer = std::make_shared<Asteroids::BulletComponentRender>();
        bulletRenderer->sprite = engine->GetSpriteFromAtlas("laserBlue01.png");
        bulletUpdate->SetStartingPos(glm::vec2(gm->position.x, gm->position.y));
        bulletUpdate->SetRotation(gm->rotation);

        gameObject->rotation = gm->rotation;
        gameObject->AddComponent(bulletRenderer);
        gameObject->AddComponent(bulletUpdate);
        gameObject->SetRadius(90);

        bullets.push_back(gameObject);
    }
    void PlayerProcessEventsComponent::TriggerPlayerDeath() {
        controlsEnabled = false;
    }
    std::list<MyEngine::GameObject*> PlayerProcessEventsComponent::GetBullets() {
        return bullets;
    }
}
