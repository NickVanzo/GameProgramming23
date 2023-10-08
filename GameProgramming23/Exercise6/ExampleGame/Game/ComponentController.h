#pragma once

#include "Component.h"

class ComponentController : public MyEngine::Component {
	void Init(rapidjson::Value&) override;
	void Update(float deltaTime) override;
	void KeyEvent(SDL_Event&) override;
	void Render(sre::RenderPass&) override;
    float mov_speed = 0.0f;
    float rot_speed = 0.0f;
    float max_speed = 0.5f;
    float friction = 0.99f;

};