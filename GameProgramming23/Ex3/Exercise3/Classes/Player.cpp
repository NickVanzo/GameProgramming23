#include "../Headers/Player.h"
#include "sre/SDLRenderer.hpp"

Player::Player(Engine &engine): engine_(engine){
    this->engine_.Attach(this);
    direction = NORD;
    std::cout << "Player constructor initialized and register to the Engine" << std::endl;
}
void Player::RemoveMeFromObserverList() {
    this->engine_.Detach(this);
    std::cout << "Player removed from the Engine" << std::endl;
}
void Player::Init()
{
}
void Player::Update(float delta_time)
{
    MovePlayer();
}
void Player::ProcessEvents(SDL_Event &event)
{
    ChangeDirectionIfPlayerMoves(event);
}
void Player::ChangeDirectionIfPlayerMoves(SDL_Event &event) {
    switch (event.key.keysym.scancode) {
        case SDL_SCANCODE_W:
            if(direction != SUD)
                direction = NORD;
            break;
        case SDL_SCANCODE_D:
            if(direction != OVEST)
                direction = EST;
            break;
        case SDL_SCANCODE_S:
            if(direction != NORD)
                direction = SUD;
            break;
        case SDL_SCANCODE_A:
            if(direction != EST)
                direction = OVEST;
            break;
        default:
            break;
    }
}
void Player::MovePlayer() {
    int movementSpeed = 5;
    switch (direction) {
        case NORD:
            y_pos += movementSpeed;
            break;
        case SUD:
            y_pos -= movementSpeed;
            break;
        case OVEST:
            x_pos -= movementSpeed;
            break;
        case EST:
            x_pos += movementSpeed;
            break;
        default:
            break;
    }
}
void Player::Render()
{
    this->engine_.snakeSprite.setPosition(glm::vec2(x_pos, y_pos));
}