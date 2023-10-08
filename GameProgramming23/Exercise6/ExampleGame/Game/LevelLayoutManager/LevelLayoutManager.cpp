//
// Created by Nicolò Vanzo on 08/10/23.
//
#include "LevelLayoutManager.h"

LevelLayoutManager::LevelLayoutManager() {
    std::cout << "Level layout in the wild" << std::endl;
}

LevelLayoutManager::~LevelLayoutManager() {
    std::cout << "Level layout freed" << std::endl;
}

void LevelLayoutManager::Init(rapidjson::Value &serializedData) {
    SetupLayoutFromJSON(serializedData);
}
void LevelLayoutManager::SetupLayoutFromJSON(rapidjson::Value &serializedData) {
    if(serializedData.HasMember("layout") && serializedData["layout"].IsArray()) {
        auto& layout = serializedData["layout"];
        for(rapidjson::SizeType i = 0; i < layout.Size(); ++i) {
            auto& row = layout[i];
            if(row.IsArray()) {
                for(rapidjson::SizeType j = 0; j < row.Size(); ++j) {
                    _layout[i][j] = row[j].GetInt();
                }
            }
        }
    }
}
void LevelLayoutManager::Update(float) {}