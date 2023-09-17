#include "../Headers/Player.h"
#include "../ITUGames.h"
#include "../Headers/Constants.h"

bool ShouldShowZero(std::chrono::time_point<std::chrono::steady_clock> spawn_time);

void Player::Init(int start_x, int start_y)
{
    spawn_time = std::chrono::steady_clock::now();
    ITUGames::Console::RenderCharacter(PLAYER_FIRST_SPRITE, start_x, start_y);
}
void Player::Init()
{
    spawn_time = std::chrono::steady_clock::now();
    ITUGames::Console::RenderCharacter(PLAYER_FIRST_SPRITE, 0, 0);
}
void HandlePlayerInit(int start_x, int start_y)
{
}
void Player::Update()
{
}
void Player::ProcessEvents()
{
    prev_pos_x = x_pos;
    prev_pos_y = y_pos;
    switch (ITUGames::Console::GetCharacter(false))
    {
    case ITUGames::Console::KEY_W:
        y_pos--;
        break;
    case ITUGames::Console::KEY_A:
        x_pos--;
        break;
    case ITUGames::Console::KEY_S:
        y_pos++;
        break;
    case ITUGames::Console::KEY_D:
        x_pos++;
    default:
        break;
    }
}
void Player::Render()
{
    ITUGames::Console::RenderCharacter(' ', prev_pos_x, prev_pos_y);
    if (ShouldShowZero(spawn_time))
    {
        ITUGames::Console::RenderCharacter(PLAYER_FIRST_SPRITE, x_pos, y_pos);
    }
    else
    {
        ITUGames::Console::RenderCharacter(PLAYER_SECOND_SPRITE, x_pos, y_pos);
    }
}

bool ShouldShowZero(std::chrono::time_point<std::chrono::steady_clock> spawn_time)
{
    std::chrono::duration<double> time_passed_since_start_program = std::chrono::steady_clock::now() - spawn_time;
    return fmod(time_passed_since_start_program.count(), 1.0) < TIME_TO_CHANGE_SPRITE_IN_SECONDS;
}