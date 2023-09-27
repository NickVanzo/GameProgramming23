//
// Created by Nicolò Vanzo on 27/09/23.
//
#include "vector";
#include "GameObject.h"

#pragma once
namespace Asteroids {
    using namespace std;
    static vector<shared_ptr<GameObject>> gameObjects = {};
    class AsteroidsManager {
    public:
        int points;
    };
}
