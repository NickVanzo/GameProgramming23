#include "MyEngine.h"

#include <random>

#include "sre/RenderPass.hpp"

namespace MyEngine {
    Engine* Engine::_instance = nullptr;
    
    Engine::Engine() {
        assert(_instance == nullptr && " Only one instance of MyEngine::Engine allowed!");
        _instance = this;
    }

    glm::vec2 Engine::GetScreenSize() const
    {
        return WIN_SIZE;
    }

    void Engine::Init() {
        // initializes random generator
        std::srand(std::time(nullptr));
        _camera.setWindowCoordinates();
        for(auto g : gameObjects)
            g->Init();
    }

    void Engine::ProcessEvents(SDL_Event& event) {
        for(auto g : gameObjects)
            g->KeyEvent(event);
    }

    void Engine::Update(float deltaTime) {
        ++frame;
        time += deltaTime;
        for(auto g : gameObjects) {
            g->Update(deltaTime);
        }
    }

    void Engine::Render()
    {
        sre::RenderPass renderPass = sre::RenderPass::create()
                .withCamera(_camera)
                .withClearColor(true, { .3f, .3f, 1, 1 })
                .build();

        sre::SpriteBatch::SpriteBatchBuilder spriteBatchBuilder = sre::SpriteBatch::create();

        for(auto g : gameObjects) {
            g->Render(spriteBatchBuilder);
        }

        auto spriteBatch = spriteBatchBuilder.build();
        renderPass.draw(spriteBatch);
    }

    void Engine::RemoveObject(std::shared_ptr<GameObject> p ) {
        p->RemoveComponents();
        auto g = std::find(gameObjects.begin(), gameObjects.end(), p);
        gameObjects.erase(g);
    }

    std::shared_ptr<GameObject> Engine::CreateGameObject(std::string name) {
        auto ret = std::make_shared<GameObject>();
        gameObjects.push_back(ret);
        return ret;
    }

    std::shared_ptr<sre::SpriteAtlas> Engine::GetAtlas() {
        return atlas;
    }

    sre::Sprite Engine::GetSpriteFromAtlas(std::basic_string<char> name) {
        return atlas->get(name);
    }
}