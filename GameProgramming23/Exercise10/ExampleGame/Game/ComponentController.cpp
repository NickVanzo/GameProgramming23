#include "ComponentController.h"

#include "glm/glm.hpp"
#include "SDL.h"

#include "Engine/Components/ComponentPhysicsBody.h"
#include "Engine/Components/ComponentRendererSprite.h"

void ComponentController::Init(rapidjson::Value& serializedData) {
	auto gameObject = GetGameObject().lock();
	if (!gameObject)
		return;

	_body = gameObject->FindComponent<ComponentPhysicsBody>();
}

void ComponentController::Update(float deltaTime) {
	auto body = _body.lock();
	if (!body)
		return;

	auto linearVelocity = body->getLinearVelocity();
	linearVelocity.x = _mov.x * _movSpeed;
	body->setLinearVelocity(linearVelocity);

	if (_jump) {
		body->addImpulse(glm::vec2(0, _jumpStrength));
		_jump = false;
	}

    HandleSpriteAnim(linearVelocity);
}

void ComponentController::HandleSpriteAnim(glm::vec2& linearVelocity) {
    auto renderer = GetGameObject().lock()->FindComponent<ComponentRendererSprite>();

    if(linearVelocity.x == 0 && _grounded) {
        SetSpriteAnim(idle, renderer);
    }

    if(linearVelocity.x != 0) {
        SetSpriteAnim(walk1, renderer);
        if(linearVelocity.x < 0) {
            auto flippingVec = glm::bvec2(true, false);
            renderer.lock()->SetSpriteFlipping(flippingVec);
        }
    }

    if(!_grounded) {
        if(linearVelocity.y > 0.5) {
            SetSpriteAnim(flyUp, renderer);
        }
        if(linearVelocity.y < 0.5) {
            SetSpriteAnim(flyDown, renderer);
        } else {
            SetSpriteAnim(fly, renderer);
        }
    }
}

void ComponentController::SetSpriteAnim(std::string & idSPrite, std::weak_ptr<ComponentRendererSprite>& renderer) {
    renderer.lock()->SetSprite(spriteAtlas, idSPrite);
}

void ComponentController::KeyEvent(SDL_Event& event) {


	// movement
	switch (event.key.keysym.sym) {
		case SDLK_a: _mov.x = -(event.type == SDL_KEYDOWN); break;
		case SDLK_d: _mov.x = +(event.type == SDL_KEYDOWN); break;
	}

	// jump
	if (_grounded && event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE)
		_jump = true;

}

void ComponentController::OnCollisionStart(ComponentPhysicsBody* other, b2Manifold* manifold) {
	if (manifold->localNormal.y > .99)
		_grounded = true;
}

void ComponentController::OnCollisionEnd(ComponentPhysicsBody* other, b2Manifold* manifold) {
	if (manifold->localNormal.y > .99)
		_grounded = false;
}