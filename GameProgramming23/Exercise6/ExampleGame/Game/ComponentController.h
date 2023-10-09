#pragma once

#include "Component.h"

class ComponentController : public MyEngine::Component {
	void Init(rapidjson::Value&) override;
	void Update(float deltaTime) override;
	void KeyEvent(SDL_Event&) override;
	void Render(sre::RenderPass&) override;
    float velocity = 0;
    float speed = 10;
    float friction = 0.99f;

};