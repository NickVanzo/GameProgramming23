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

    if(serializedData.HasMember("layout")) {
//        auto& projectionParams = serializedData["components"];
        std::cout << "Member layout found in serialized data" << std::endl;
    } else {
        std::cout << "Member layout not found in serialized data" << std::endl;
    }
}
void LevelLayoutManager::Update(float) {
    std::cout << "updating" << std::endl;
}