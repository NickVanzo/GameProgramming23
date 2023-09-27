#include "../Headers/Player.h"
#include "sre/SDLRenderer.hpp"
#include "../Headers/Asteroids.h"

namespace Asteroids {
    Player::Player() {
        auto engine = Engine::GetInstance();
//    engine->Attach(this);
        std::cout << "Player constructor initialized and register to the Engine" << std::endl;
    }
    Player::~Player(){
        std::cout << "Player destructor called" << std::endl;
    }
    void Player::Init() {}
    void Player::Update(float delta_time) {}
    void Player::ProcessEvents(SDL_Event &event) {}
    void Player::Render(sre::SpriteBatch::SpriteBatchBuilder &) {}

    void Player::RemoveMeFromObserverList() {
        auto engine = Engine::GetInstance();
        engine->Detach(this);
        std::cout << "Player removed from the Engine" << std::endl;
    }

}
