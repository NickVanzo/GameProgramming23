#include "../Headers/Engine.h"
Engine* Engine::engineInstance_{nullptr};
std::mutex Engine::mutex_;
Engine::Engine() {}
void Engine::Init()
{
    renderer.setWindowSize(window_size);
    renderer.init();
    camera.setWindowCoordinates();
    atlas = sre::SpriteAtlas::create("data/snake.json", "data/snake.png");
    snakeSprite = atlas->get("snake-body.png");
    snakeSprite.setPosition(initial_position_snake);
    sprite = atlas->get("berry.png");

    renderer.frameUpdate = [this](float delta_time) {
        Update(delta_time);
    };
    renderer.keyEvent = [this](SDL_Event &event) {
        ProcessEvents(event);
    };
    renderer.frameRender = [this]() {
        Render();
    };
    renderer.startEventLoop();
}
void Engine::Update(float delta_time)
{
    NotifyUpdate(delta_time);
}
void Engine::NotifyUpdate(float delta_time)
{
    auto iterator = listObserver.begin();
    while(iterator != listObserver.end()) {
        (*iterator)->Update(delta_time);
        ++iterator;
    }
}
void Engine::ProcessEvents(SDL_Event &event)
{
    NotifyProcessEvents(event);
}
void Engine::NotifyProcessEvents(SDL_Event &event) {
    auto iterator = listObserver.begin();
    while(iterator != listObserver.end())
    {
        (*iterator)->ProcessEvents(event);
        ++iterator;
    }
}
void Engine::Render()
{
    sre::RenderPass renderPass = sre::RenderPass::create()
            .withCamera(camera)
            .withClearColor(true, { .3f, .3f, 1, 1 })
            .build();
    sre::SpriteBatch::SpriteBatchBuilder spriteBatchBuilder
            = sre::SpriteBatch::create();
    // send spriteBatchBuilder to your game elements, so that they can add their sprites for rendering
    spriteBatchBuilder.addSprite(sprite);
    spriteBatchBuilder.addSprite(snakeSprite);
    auto spriteBatch = spriteBatchBuilder.build();
    renderPass.draw(spriteBatch);
    NotifyRender();
}
void Engine::NotifyRender() {
    auto iterator = listObserver.begin();
    while(iterator != listObserver.end()) {
        (*iterator)->Render();
        ++iterator;
    }
}
void Engine::Attach(GameObject *observer) {
    listObserver.push_front(observer);
}
void Engine::Detach(GameObject *observer) {
    listObserver.remove(observer);
}
Engine* Engine::GetInstance() {
    std::lock_guard<std::mutex> lock(mutex_);
    if(engineInstance_ == nullptr){
        engineInstance_ = new Engine();
    }
    return engineInstance_;
}

