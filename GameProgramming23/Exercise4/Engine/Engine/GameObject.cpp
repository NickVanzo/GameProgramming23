#include "GameObject.h"

#include "sre/RenderPass.hpp"

#include "MyEngine.h"
#include "Component.h"
#include "Logger.h"

namespace MyEngine {
    GameObject::~GameObject() {
        std::cout << "Destroyed object: " << _name << std::endl;
        RemoveComponents();
    }

	void GameObject::Init() {
		for (auto& component : _components)
			component->Init();
	}

	void GameObject::Update(float deltaTime) {
		for (auto& component : _components)
			component->Update(deltaTime);

	}

	void GameObject::Render(sre::SpriteBatch::SpriteBatchBuilder& spriteBatchBuilder) {
		for (auto& component : _components)
			component->Render(spriteBatchBuilder);
	}

	void GameObject::KeyEvent(SDL_Event& e) {
		for (auto& component : _components)
			component->KeyEvent(e);
	}

	void GameObject::AddComponent(std::unique_ptr<Component> p_component) {
		_components.push_back(std::move(p_component));
	}

    void GameObject::RemoveComponents() {
//        for(auto c : _components) {
//            c->_gameObject = nullptr;
//        }
//        _components.clear();
    }

    std::list<std::unique_ptr<Component>> GameObject::GetComponents() {
//        return _components;
    }

	std::string GameObject::GetName() {
		return _name;
	}

	void GameObject::SetName(std::string p_name) {
		_name = p_name;
	}

    void GameObject::SetRadius(float r) {
        this->radius = r;
    }
}