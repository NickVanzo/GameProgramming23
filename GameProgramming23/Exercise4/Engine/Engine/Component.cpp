#include "Component.h"

#include "Logger.h"

namespace MyEngine {
    std::weak_ptr<GameObject> Component::GetGameObject() {
		return _gameObject;
	}
}