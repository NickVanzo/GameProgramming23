//
// Created by Nicolò Vanzo on 08/10/23.
//

#include "Engine/Component.h"
#pragma once

class LevelLayoutManager: public MyEngine::Component {
public:
    LevelLayoutManager();
    ~LevelLayoutManager();
    void Init(rapidjson::Value& serializedData) override;
    void Update(float) override;
    void SetupLayoutFromJSON(rapidjson::Value &serializedData);
private:
    static const int ROWS = 5;
    static const int COLUMNS = 4;
    int _layout[ROWS][COLUMNS];
};
