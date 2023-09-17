#pragma once
#include "./GameObject.h"
class Score: public GameObject
{
    void Init() override;
    void Init(int pos_x, int pos_y) override;
    void ProcessEvents() override;
    void Update() override;
    void Render() override;
};