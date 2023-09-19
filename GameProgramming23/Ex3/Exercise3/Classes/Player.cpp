#include "../Headers/Player.h"
#include "sre/SDLRenderer.hpp"

Player::Player(Engine &engine): engine_(engine){
    this->engine_.Attach(this);
    position.currentPosX = 20;
    position.currentPosY = 20;
    position.nextPosX = 0;
    position.nextPosX = 0;
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
            position.currentPosY += movementSpeed;
            break;
        case SUD:
            position.currentPosY -= movementSpeed;
            break;
        case OVEST:
            position.currentPosX -= movementSpeed;
            break;
        case EST:
            position.currentPosX += movementSpeed;
            break;
        default:
            break;
    }
}
void Player::Render()
{
    this->engine_.snakeSprite.setPosition(glm::vec2(position.currentPosX, position.currentPosY));
}