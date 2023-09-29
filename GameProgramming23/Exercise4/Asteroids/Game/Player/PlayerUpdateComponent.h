//
// Created by Nicolò Vanzo on 22/09/23.
//
#include "Engine/Component.h"

#ifndef SIMPLERENDERENGINEPROJECT_PLAYERCOMPONENTINPUT_H
#define SIMPLERENDERENGINEPROJECT_PLAYERCOMPONENTINPUT_H
namespace Asteroids {
    class PlayerUpdateComponent: public MyEngine::Component {
    public:
        PlayerUpdateComponent(std::weak_ptr<MyEngine::GameObject>);
        const glm::vec2 movDirection = glm::vec2(1,0);
        void Init() override;
        void Update(float) override;
        void KeyEvent(SDL_Event&) override;
        void TriggerPlayerDeath();
    private:
        void Shoot();
        float speed = 90.0f;
        bool controlsEnabled = true;
    };
}
#endif //SIMPLERENDERENGINEPROJECT_PLAYERCOMPONENTINPUT_H
