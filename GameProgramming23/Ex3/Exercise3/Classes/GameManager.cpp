//
// Created by Nicolò Vanzo on 27/09/23.
//

#include "../Headers/GameManager.h"
#include "../Headers/Asteroids.h"
#include "../Headers/Player.h"

namespace Asteroids {
    using namespace std;
    void GameManager::StartGame() {
        cout << "Objects: " << gameObjects.size() << endl;
        shared_ptr<Asteroids::Player> p = make_shared<Asteroids::Player>();
        Asteroids::gameObjects.push_back(p);
        cout << "Objects: " << Asteroids::gameObjects.size() << endl;
        Asteroids::gameObjects.erase(Asteroids::gameObjects.begin());
    }
}