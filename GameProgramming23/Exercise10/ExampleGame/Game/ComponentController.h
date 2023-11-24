#pragma once

#include "Engine/Component.h"
#include "Engine/Components/ComponentRendererSprite.h"
class ComponentController : public MyEngine::Component {
	void Init(rapidjson::Value&) override;
	void Update(float deltaTime) override;
	void KeyEvent(SDL_Event&) override;
	void OnCollisionStart(ComponentPhysicsBody* other, b2Manifold* manifold) override;
	void OnCollisionEnd(ComponentPhysicsBody* other, b2Manifold* manifold) override;
    void HandleSpriteAnim(glm::vec2&);
    void SetSpriteAnim(std::string&, std::weak_ptr<ComponentRendererSprite>&);
private:
	std::weak_ptr<ComponentPhysicsBody> _body;
	glm::vec3 _mov;
	bool _jump;
	bool _grounded;

	float _movSpeed = 2;
	float _jumpStrength = 5;

    std::string spriteAtlas = "platformer-art-deluxe";
    std::string idle = "19.png";
    std::string walk1 = "20.png";
    std::string walk2 = "21.png";
    std::string flyUp = "26.png";
    std::string fly = "27.png";
    std::string flyDown = "28.png";
};