#pragma once
#include <chrono>
#include "./GameObject.h"
class Engine: public GameObject
{
public:
    std::chrono::time_point<std::chrono::steady_clock> time_end_computation;
    std::chrono::time_point<std::chrono::steady_clock> time_start;
    std::chrono::time_point<std::chrono::steady_clock> time_end;
    std::chrono::duration<double> time_elapsed; 
    double seconds_to_wait_to_change_sprite = 0.5;
    double target_fps = 60.0;
    std::chrono::duration<double> target_frame_time = (std::chrono::duration<double>)1.0 / target_fps;
    double fps = 0;

    void Init() override;
    void Init(int pos_x, int pos_y) override;
    void ProcessEvents() override;
    void Update() override;
    void Render() override;
    double GetFPS();
    double GetTimeElapsedMs();
    std::chrono::duration<double> GetTimeComputationMs();
};