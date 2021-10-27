#include <cmath>
#include "Game.h"

Game::Game()
:mWindow(nullptr)
,mRenderer(nullptr)
,mIsRunning(true)
,mTicksCount(0)
,mPaddleDir(0)
{
	mBallPos = { 1024.0 / 2.0, 768.0 / 2.0 };
    mP = { THICKNESS, 768.0 / 2.0 };
    mBallVel = { -200.0f, 235.0f };
}

bool Game::Initialize()
{
    int sdlResult = SDL_Init(SDL_INIT_VIDEO);

    if (sdlResult != 0)
    {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return false;
    }

    mWindow = SDL_CreateWindow(
        "Game Programming in C++ {chapter1}",
        100,
        100,
        1024,
        768,
        0
    );

    if (!mWindow)
    {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return false;
    }

    mRenderer = SDL_CreateRenderer(
        mWindow,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    if (!mRenderer)
    {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        return false;
    }

    return true;    
}

void Game::RunLoop()
{
    while (mIsRunning)
    {
        ProcessInput();
        UpdateGame();
        GenerateOutput();
    }
}


void Game::Shutdown()
{
    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
}

void Game::ProcessInput()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            mIsRunning = false;
            break;
        }
    }

    const Uint8 *state = SDL_GetKeyboardState(NULL);

    if (state[SDL_SCANCODE_ESCAPE])
    {
        mIsRunning = false;
    }
    
    mPaddleDir = 0;
    if (state[SDL_SCANCODE_W])
    {
        mPaddleDir -= 1;
    }

    if (state[SDL_SCANCODE_S])
    {
        mPaddleDir += 1;
    }
}

void Game::UpdateGame()
{
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));

    float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;

    mTicksCount = SDL_GetTicks();

    if (deltaTime > 0.05f)
    {
        deltaTime = 0.05f;
    }


    if (mPaddleDir != 0)
    {
        mP.y += mPaddleDir * 300.0f * deltaTime;

        if (mP.y < PADDLEH / 2.0f + THICKNESS) mP.y = PADDLEH / 2.0f + THICKNESS;
        if (mP.y > (768.0f - PADDLEH / 2.0f - THICKNESS)) mP.y = (768.0f - PADDLEH / 2.0f - THICKNESS);
    }

    mBallPos.x += mBallVel.x * deltaTime;
    mBallPos.y += mBallVel.y * deltaTime;

    if (mBallPos.y <= THICKNESS * 1.5f && mBallVel.y < 0.0f) mBallVel.y *= -1;
    if (mBallPos.y >= 768.0f - THICKNESS * 1.5f && mBallVel.y > 0.0f) mBallVel.y *= -1;
    if (mBallPos.x >= 1024.0f - 1.5f * THICKNESS && mBallVel.x > 0.0f) mBallVel.x *= -1; 

    float diffY = std::fabs(mBallPos.y - mP.y);

    if (diffY <= PADDLEH / 2.0f + THICKNESS / 2.0f && mBallPos.x <= THICKNESS * 2.0f && mBallPos.x >= THICKNESS * 1.5f)
    {
        mBallVel.x *= -1;
    }
}

void Game::GenerateOutput()
{
    SDL_SetRenderDrawColor(
        mRenderer,
        0,
        0,
        255,
        255
    );

    SDL_RenderClear(mRenderer);

    SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);

    SDL_Rect wall { // 上墙壁
        0,
        0,
        1024,
        THICKNESS
    };

    SDL_RenderFillRect(mRenderer, &wall);

    wall = { // 下墙壁
        0,
        768 - THICKNESS,
        1024,
        THICKNESS
    };

    SDL_RenderFillRect(mRenderer, &wall);

    wall = { // 右墙壁
        1024 - THICKNESS,
        0,
        THICKNESS,
        768
    };

    SDL_RenderFillRect(mRenderer, &wall);

    SDL_Rect ball{
        static_cast<int>(mBallPos.x - THICKNESS / 2),
        static_cast<int>(mBallPos.y - THICKNESS / 2),
        THICKNESS,
        THICKNESS
    };

    SDL_RenderFillRect(mRenderer, &ball);

    SDL_Rect p{
        static_cast<int>(mP.x - THICKNESS / 2),
        static_cast<int>(mP.y - PADDLEH / 2),
        THICKNESS,
        PADDLEH
    };

    SDL_RenderFillRect(mRenderer, &p);

    SDL_RenderPresent(mRenderer);
}
