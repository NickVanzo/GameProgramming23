#pragma once

#include "Engine/Component.h"
#include "Engine/GameObject.h"

class ComponentController : public MyEngine::Component {
	void Init(rapidjson::Value&) override;
	void Update(float deltaTime) override;
	void KeyEvent(SDL_Event&) override;
	void OnCollisionStart(ComponentPhysicsBody* other) override;
private:
    bool linearVelocitySet = false;
	glm::vec3 _mov;
	float mov_speed;
	float rot_speed;
    float impulseForce;
    int coinsPickedUp = 0;
    void ApplyImpulse();
    void Move(float deltaTime);
    bool IsWall(const std::string& name);
    void SetBirdValuesFromJSON(rapidjson::Value&);
    void SetValuesFromJSON(rapidjson::Value&);
    void SetDefaultValues();
    bool JSONIsValid(rapidjson::Value&);
    void SetLinearVelocity(float);
};