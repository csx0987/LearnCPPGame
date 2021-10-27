#pragma once
#include <SDL.h>

const int THICKNESS = 15;
const int PADDLEH = 60;

struct Vector2
{
    float x;
    float y;
};

class Game
{
private:
    SDL_Window *mWindow;
    SDL_Renderer *mRenderer;
    bool mIsRunning;

    Vector2 mBallPos;
    Vector2 mP;

    Uint32 mTicksCount;

    int mPaddleDir;

    Vector2 mBallVel;

    void ProcessInput(); // 处理输入
    void UpdateGame(); // 
    void GenerateOutput();
public:
    Game();

    bool Initialize();
    void RunLoop();
    void Shutdown();
};