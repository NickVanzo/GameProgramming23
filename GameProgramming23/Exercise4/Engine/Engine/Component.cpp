#include "Component.h"

#include "Logger.h"

namespace MyEngine {
    std::shared_ptr<GameObject> Component::GetGameObject() {
		return _gameObject;
	}
}