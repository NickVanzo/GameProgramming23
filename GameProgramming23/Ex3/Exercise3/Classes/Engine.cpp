#include "../Headers/Engine.h"
#include <random>
#include "../ITUGames.h"

void Engine::Init()
{
    std::srand(std::time(nullptr));
    ITUGames::Console::InitScreenForRendering();
}
void Engine::Init(int pos_x, int pos_y) {};
void Engine::Update()
{
    fps = 1.0 / time_elapsed.count();
}
void Engine::ProcessEvents()
{
}
void Engine::Render()
{
    ITUGames::Console::GotoTop();
    std::cout << "Elapsed(ms) : " << time_elapsed.count() * 100 << std::endl;
    std::cout << "FPS: " << fps << std::endl;
    std::cout << "Computation time (ms): " << (time_elapsed).count() * 100 << std::endl;
    std::cout << "Target Frame Time (ms): " << target_frame_time.count() * 100 << std::endl;
    std::cout << "Target FPS: " << target_fps << std::endl;
}
std::chrono::duration<double> Engine::GetTimeComputationMs()
{
    return time_end_computation - time_start;
}
double Engine::GetFPS()
{
    return fps;
}
double Engine::GetTimeElapsedMs()
{
    return time_elapsed.count() * 100;
}