#pragma once

#include "Engine/Component.h"
#include "Engine/GameObject.h"

class ComponentController : public MyEngine::Component {
	void Init(rapidjson::Value&) override;
	void Update(float deltaTime) override;
	void KeyEvent(SDL_Event&) override;
	void OnCollisionStart(ComponentPhysicsBody* other) override;
private:
	glm::vec3 _mov;
	float mov_speed;
	float rot_speed;
    float impulseForce;
    void ApplyImpulse();
    void Move(float deltaTime);
    void SetBirdValuesFromJSON(rapidjson::Value&);
    void SetValuesFromJSON(rapidjson::Value&);
    void SetDefaultValues();
    bool JSONIsValid(rapidjson::Value&);
};