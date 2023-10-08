//
// Created by Nicolò Vanzo on 08/10/23.
//

#include "../../Engine/Engine/GameObject.h"
#include "../../Engine/Engine/MyEngine.h"

#pragma once

class LevelLayoutManager: public MyEngine::GameObject {
public:
    LevelLayoutManager(rapidjson::Value& data);
    ~LevelLayoutManager();
    void SetupLayoutFromJSON(rapidjson::Value &serializedData);
private:
    static const int ROWS = 5;
    static const int COLUMNS = 4;
    int _layout[ROWS][COLUMNS];


};
