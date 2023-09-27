#include "../Headers/Player.h"
#include "sre/SDLRenderer.hpp"

Player::Player(std::shared_ptr<Engine> engine): engine_(engine){
    this->engine_->Attach(this);
    std::cout << "Player constructor initialized and register to the Engine" << std::endl;
}
void Player::RemoveMeFromObserverList() {
    this->engine_->Detach(this);
    std::cout << "Player removed from the Engine" << std::endl;
}
