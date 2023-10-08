//
// Created by Nicolò Vanzo on 27/09/23.
//
#include "MyEngine.h"
#include "../LevelLayoutManager/LevelLayoutManager.h"
#pragma once

class GameManager {
public:
    ~GameManager();
    void StartGame(rapidjson::Value& data);
    std::shared_ptr<MyEngine::GameObject> lvlLayoutManager;
};
