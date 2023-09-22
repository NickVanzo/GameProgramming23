#include "PlayerProcessEventsComponent.h"
#include "PlayerUpdateComponent.h"
#include "sre/SDLRenderer.hpp"
#include "MyEngine.h"

namespace Asteroids {
    void PlayerProcessEventsComponent::KeyEvent(SDL_Event& event) {
        MyEngine::GameObject* parent = GetGameObject();
        switch (event.key.keysym.scancode) {
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
