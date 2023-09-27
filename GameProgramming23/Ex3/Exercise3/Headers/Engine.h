#pragma once
#include <chrono>
#include <list>
#include "./GameObject.h"
#include "sre/SDLRenderer.hpp"
#include "sre/SpriteAtlas.hpp"

class Engine
{
private:
    static Engine * engineInstance_;
    static std::mutex mutex_;
protected:
    Engine();
    ~Engine();
public:
    Engine(Engine &other) = delete;
    void operator=(const Engine &) = delete;
    std::list<GameObject*> listObserver;
    sre::SDLRenderer renderer;
    sre::Camera camera;
    std::shared_ptr<sre::SpriteAtlas> atlas;
    glm::vec2 window_size = glm::vec2(800, 600);

    void Init();
    void ProcessEvents(SDL_Event &event);
    void Update(float delta_time);
    void Render();
    void Attach(GameObject* observer);
    void Detach(GameObject* observer);
    void NotifyUpdate(float delta_time);
    void NotifyProcessEvents(SDL_Event &event);
    void NotifyRender(sre::SpriteBatch::SpriteBatchBuilder&);
    static Engine* GetInstance();
};
