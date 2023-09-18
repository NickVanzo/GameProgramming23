#include "../Headers/Player.h"

Player::Player(Engine &engine): engine_(engine){
    this->engine_.Attach(this);
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
}
void Player::ProcessEvents(SDL_Event &event)
{
    switch (event.key.keysym.scancode) {
        case SDL_SCANCODE_W:
            y_pos += 10;
            break;
        case SDL_SCANCODE_D:
            x_pos += 10;
            break;
        case SDL_SCANCODE_S:
            y_pos -= 10;
            break;
        case SDL_SCANCODE_A:
            x_pos -= 10;
            break;
        default:
            break;
    }
}
void Player::Render()
{
}