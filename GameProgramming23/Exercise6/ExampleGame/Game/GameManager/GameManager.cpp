//
// Created by Nicolò Vanzo on 08/10/23.
//

#include "MyEngine.h"
#include "ComponentFactory.h"
using namespace std;

GameManager::~GameManager() {
    cout<<"Destructor called in GameManager"<<endl;
}
void GameManager::StartGame(rapidjson::Value& data) {
    auto engine = MyEngine::Engine::GetInstance();
    lvlLayoutManager = engine->CreateGameObject("LEVELMANAGER");

}