//
// Created by Nicolò Vanzo on 02/10/23.
//

#include "Factory.h"
#include "../Game/Player/PlayerUpdateComponent.h"
#include "../Game/Player/PlayerComponentRenderer.h"
#include <cstring>

Factory::Factory() {
    engine = MyEngine::Engine::GetInstance();
}

std::shared_ptr<MyEngine::GameObject> Factory::CreateGameObject(const std::string& id) {
    const char * idCStr = id.c_str();

    if(strcmp(idCStr, "PLAYER") == 0) {
        std::cout << "Creating game object with ID: " << id << std::endl;
        return CreatePlayer();
    }
}

std::shared_ptr<MyEngine::GameObject> Factory::CreatePlayer() {
    auto gameObjectData = engine->GetGameDataDoc();
    std::shared_ptr<MyEngine::GameObject> playerGameObject = engine->CreateGameObject("Player");
    rapidjson::Document& doc = (*gameObjectData);
    rapidjson::Value& rootGameObject = doc["root"];
    if(rootGameObject.HasMember("gameObjects")) {
        rapidjson::Value& arrayOfGameObjects = rootGameObject["gameObjects"];
        for(int i = 0; i < arrayOfGameObjects.Size(); i++) {
            std::string id = arrayOfGameObjects[i]["id"].GetString();
            if(id == "PLAYER") {
                if(arrayOfGameObjects[i].HasMember("metadata")) {
                    if(arrayOfGameObjects[i]["metadata"].HasMember("radius")) {
                        playerGameObject->SetRadius(arrayOfGameObjects[i]["metadata"]["radius"].GetFloat());
                    }
                    if(arrayOfGameObjects[i].HasMember("components")) {
                        AppendComponentsToPlayer(playerGameObject);
                    }
                }
            }
        }
    }
    return playerGameObject;
}

void Factory::AppendComponentsToPlayer(const std::shared_ptr<MyEngine::GameObject>& player) {
    auto playerController = std::make_shared<Asteroids::PlayerUpdateComponent>(player);
    auto playerRenderer = std::make_shared<Asteroids::PlayerComponentRenderer>(player);
    playerRenderer->sprite = engine->atlas->get("playerShip1_blue.png");
    playerRenderer->deathSprite = engine->atlas->get("bang.png");

    player->AddComponent(playerController);
    player->AddComponent(playerRenderer);
}

