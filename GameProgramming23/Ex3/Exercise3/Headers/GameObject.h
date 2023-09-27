#pragma once
#include "sre/SDLRenderer.hpp"

    class GameObject
    {
    private:
    public:
        std::vector<std::shared_ptr<GameObject>> components = {};
        glm::vec2 position = glm::vec2(0,0);
        float rotation = 90;
        float radius = 90;
        void Init();
        void Update(float delta_time);
        void ProcessEvents(SDL_Event &event);
        void Render(sre::SpriteBatch::SpriteBatchBuilder&);
    };
