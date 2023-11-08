#include "ComponentBackground.h"

#include "Engine/MyEngine.h"
#include "Engine/Components/ComponentRendererSprite.h"

void ComponentBackground::Init(rapidjson::Value& serializedData) {
	auto gameObject = GetGameObject().lock();
	if (!gameObject)
		return;

	auto p_spriteComp = gameObject->FindComponent<ComponentRendererSprite>();

	if (auto spriteComp = p_spriteComp.lock()) {
		sre::Sprite* sprite = spriteComp->GetSprite();
		float scale = MyEngine::Engine::GetInstance()->GetScreenSize().y / sprite->getSpriteSize().y;
		sprite->setScale({ scale * 2 , scale });
	}
}

void ComponentBackground::Update(float deltaTime) {
    auto engine = MyEngine::Engine::GetInstance();
    auto gm = engine->GetGameObject("camera");
    auto pos = gm.lock()->GetPosition();
    auto p_spriteComp = GetGameObject().lock()->FindComponent<ComponentRendererSprite>();

    if (auto spriteComp = p_spriteComp.lock()) {
        sre::Sprite* sprite = spriteComp->GetSprite();
        sprite->setPosition(glm::vec2 (pos.x - 4 * sprite->getSpriteSize().x / 2, sprite->getPosition().y));
    }
}