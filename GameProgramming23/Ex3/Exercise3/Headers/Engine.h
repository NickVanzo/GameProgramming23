#pragma once
#include <chrono>
#include <list>
#include "./GameObject.h"
#include "sre/SDLRenderer.hpp"
#include "sre/SpriteAtlas.hpp"


class Engine: public GameObject
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
    sre::Sprite sprite;
    sre::Sprite snakeSprite;
    glm::vec2 window_size = glm::vec2(800, 600);
    glm::vec2 initial_position_snake = glm::vec2(400, 400);

    void Init() override;
    void ProcessEvents(SDL_Event &event) override;
    void Update(float delta_time) override;
    void Render() override;
    void Attach(GameObject* observer);
    void Detach(GameObject* observer);
    void NotifyUpdate(float delta_time);
    void NotifyProcessEvents(SDL_Event &event);
    void NotifyRender();
    static Engine* GetInstance();
};
