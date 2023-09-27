//
// Created by Nicolò Vanzo on 27/09/23.
//

#include "../Headers/GameObject.h"
    void GameObject::Init() {
        for(auto c : components) {
            c->Init();
        }
    }
    void GameObject::Update(float delta_time) {
        for(auto c : components)
            c->Update(delta_time);
    }
    void GameObject::Render(sre::SpriteBatch::SpriteBatchBuilder& render) {
        for(auto c: components)
            c->Render(render);
    }
    void GameObject::ProcessEvents(SDL_Event &event) {
        for(auto c: components) {
            c->ProcessEvents(event);
        }
    }
