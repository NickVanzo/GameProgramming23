#pragma once
class GameObject
{
private:
public:
    int pos_x;
    int pos_y;
    virtual void Init() = 0;
    virtual void Init(int pos_x, int pos_y) = 0;
    virtual void Update() = 0;
    virtual void ProcessEvents() = 0;
    virtual void Render() = 0;
};