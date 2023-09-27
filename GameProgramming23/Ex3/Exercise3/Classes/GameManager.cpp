//
// Created by Nicolò Vanzo on 27/09/23.
//

#include "../Headers/GameManager.h"
#include "../Headers/Asteroids.h"
#include "../Headers/Player.h"

namespace Asteroids {
    using namespace std;
    void GameManager::StartGame() {
        Engine* engine = Engine::GetInstance();
        cout << "Objects: " << gameObjects.size() << endl;
        sre::Sprite sprite = engine->atlas->get("playerShip1_blue.png");
        cout << "SPRITE FOUND" << endl;
        gameObjects.push_back(
                make_shared<Player>(
                        sprite
                ));

        cout << "Objects: " << Asteroids::gameObjects.size() << endl;
        gameObjects.erase(Asteroids::gameObjects.begin());
    }
}