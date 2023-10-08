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
private:
    int layout[5][5];
};
