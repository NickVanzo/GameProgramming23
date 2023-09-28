#include "MyEngine.h"

#include <random>

#include "sre/RenderPass.hpp"

namespace MyEngine {
    Engine* Engine::_instance = nullptr;
    Engine::~Engine() {
        std::cout << "Distruttore di MyEngine" << std::endl;
        gameObjects.clear();
    }
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
        gameManager = std::make_shared<GameManager>();
        gameManager->StartGame();
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

    void Engine::RemoveObject(std::shared_ptr<MyEngine::GameObject> p) {
        for(int i = 0; i < gameObjects.size(); i++) {
            if(gameObjects[i] != nullptr && gameObjects[i] == p) {
                std::cout << "Asteroid to destroy found " << std::endl;
                std::cout << "References: " << p.use_count() << std::endl;
                gameObjects.erase(gameObjects.begin() + i);
            }
        }
    }

    std::shared_ptr<GameObject> Engine::CreateGameObject(std::string name) {
        auto ret = std::make_shared<GameObject>();
        ret->SetName(name);
        gameObjects.push_back(ret);
        std::cout << "Added game object to gameObjects with name "<< name <<"! Now the vector has length: " << gameObjects.size() << std::endl;
        return ret;
    }
}