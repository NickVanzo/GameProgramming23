#pragma once
#include <chrono>
#include "./Constants.h"
#include "./GameObject.h"
class Player: public GameObject
{
public:
    char player_primary_sprite = '0';
    char player_secondary_sprite = 'O';
    int x_pos = 20;
    int y_pos = 10;
    int prev_pos_x = 0;
    int prev_pos_y = 0;
    std::chrono::time_point<std::chrono::steady_clock> spawn_time = std::chrono::steady_clock::now();

    void Init(int start_x, int start_y) override;
    void Init() override;
    void ProcessEvents() override;
    void Update() override;
    void Render() override;
};