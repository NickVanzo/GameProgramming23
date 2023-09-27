//
// Created by Nicolò Vanzo on 27/09/23.
//
#include "MyEngine.h"
#include "../AsteroidSpawner/AsteroidSpawner.h"
#pragma once

class GameManager {
public:
    void StartGame();
    void CreatePlayer();
    void CreateAsteroidSpawner();
    std::shared_ptr<MyEngine::GameObject> player;
    std::shared_ptr<MyEngine::GameObject> upperSpawner;
    std::shared_ptr<Asteroids::AsteroidSpawner> lowerSpawner;
};
