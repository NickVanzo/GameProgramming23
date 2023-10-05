//
// Created by Nicolò Vanzo on 02/10/23.
//

#include "../../Engine/Engine/Component.h"
#include "../../Engine/Engine/MyEngine.h"
#pragma once

class Factory {
public:
    Factory();
    std::shared_ptr<MyEngine::GameObject> CreateGameObject(const std::string& id);
private:
    std::shared_ptr<MyEngine::GameObject> CreatePlayer();
    void AppendComponentsToPlayer(const std::shared_ptr<MyEngine::GameObject>&);
    MyEngine::Engine* engine;
};


