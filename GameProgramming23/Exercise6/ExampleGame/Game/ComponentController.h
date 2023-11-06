#pragma once

#include "Component.h"

class ComponentController : public MyEngine::Component {
	void Init(rapidjson::Value&) override;
	void Update(float deltaTime) override;
	void KeyEvent(SDL_Event&) override;
	void Render(sre::RenderPass&) override;
    glm::vec3 yAxis = glm::vec3(0,1,0);
    float speedRotation = 50;
    float angle = glm::radians(4.0f);
    float velocity = 0;
    float rotation = 0;
    float speed = 30;
    float friction = 0.99f;

};