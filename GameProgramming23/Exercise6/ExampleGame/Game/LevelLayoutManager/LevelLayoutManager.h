//
// Created by Nicolò Vanzo on 08/10/23.
//

#include "../../Engine/Engine/GameObject.h"
#include "../../Engine/Engine/MyEngine.h"
#include "../../costants/Costants.h"
#pragma once

class LevelLayoutManager: public MyEngine::GameObject {
public:
    LevelLayoutManager(rapidjson::Value& data);
    void Init(rapidjson::Value& data);
    ~LevelLayoutManager();
    void SetupLayoutFromJSON(rapidjson::Value &serializedData);
private:
    int _layout[MyEngine::ROWS][MyEngine::COLUMNS];
};
