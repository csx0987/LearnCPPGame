#include <cmath>
#include <algorithm>
#include <SDL_image.h>
#include "Game.h"
#include "Actor.h"
#include "SpriteComponent.h"
#include "Ship.h"
#include "Asteroid.h"
#include "Random.h"

Game::Game()
:mWindow(nullptr)
,mRenderer(nullptr)
,mIsRunning(true)
,mUpdatingActors(false)
,mShip(nullptr)
,mRebirthTime(3.0f)
{

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
        "Game Programming in C++ {chapter2}",
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

    if (IMG_Init(IMG_INIT_PNG) == 0)
    {
        SDL_Log("Unable to initialize SDL_image: %s", SDL_GetError());
        return false;
    }

    LoadData();

    mTicksCount = SDL_GetTicks();

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
    UnloadData();
    IMG_Quit();
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

    mUpdatingActors = true;

    for (auto actor : mActors)
    {
        actor->ProcessInput(state);
    }

    mUpdatingActors = false;
    
    // mShip->ProcessKeyboard(state);
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

    // ??????????????????
    if (mShip == nullptr)
    {
        if (mRebirthTime <= 0.0f)
        {
            mShip = new Ship(this);
            mShip->SetPosition(Vector2(512.0f, 384.0f));
            mShip->SetRotation(Math::PiOver2);
            mRebirthTime = 3.0f;
        }
        else
        {
            mRebirthTime -= deltaTime;
        }
    }

    mUpdatingActors = true;

    for (auto actor : mActors)
    {
        actor->Update(deltaTime);
    }

    mUpdatingActors = false;

    for (auto pending : mPendingActors)
    {
        mActors.emplace_back(pending);
    }

    mPendingActors.clear();

    std::vector<Actor*> deadActors;

    for (auto actor : mActors)
    {
        if (actor->GetState() == Actor::EDead)
        {
            deadActors.emplace_back(actor);
        }
    }

    // actor ???????????????mActors?????????
    for (auto actor : deadActors)
    {
        delete actor;
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

    for (auto sprite : mSprites)
    {
        sprite->Draw(mRenderer);
    }

    SDL_RenderPresent(mRenderer);
}

void Game::AddActor(Actor* actor)
{
    if (mUpdatingActors)
    {
        mPendingActors.emplace_back(actor);
    }
    else
    {
        mActors.emplace_back(actor);
    }
}

void Game::RemoveActor(Actor* actor)
{
    auto it = std::find(mPendingActors.begin(), mPendingActors.end(), actor);
    if (it != mPendingActors.end())
    {
        std::iter_swap(it, mPendingActors.end() - 1);
        mPendingActors.pop_back();
    }

    it = std::find(mActors.begin(), mActors.end(), actor);
    if (it != mActors.end())
    {
        std::iter_swap(it, mActors.end() - 1);
        mActors.pop_back();
    }
}

void Game::AddSprite(SpriteComponent* sprite)
{
    int myDrawOrder = sprite->GetDrawOrder();
    auto it = mSprites.begin();

    for (; it != mSprites.end(); it++)
    {
        if (myDrawOrder < (*it)->GetDrawOrder()) break;
    }

    mSprites.insert(it, sprite);
}

void Game::RemoveSprite(SpriteComponent* sprite)
{
    auto iter = std::find(mSprites.begin(), mSprites.end(), sprite);
	mSprites.erase(iter);
}

void Game::AddAsteroid(Asteroid *ast)
{
    mAsteroids.push_back(ast);
}

void Game::RemoveAsteroid(Asteroid *ast)
{
    auto iter = std::find(mAsteroids.begin(),
        mAsteroids.end(), ast);
    
    if (iter != mAsteroids.end())
    {
        mAsteroids.erase(iter);
    }
}

SDL_Texture* Game::GetTexture(const std::string &fileName)
{
    SDL_Texture *tex = nullptr;

    auto it = mTextures.find(fileName);
    if (it != mTextures.end())
    {
        tex = it->second;
    }
    else
    {
        SDL_Surface *surf = IMG_Load(fileName.c_str());
        if (!surf)
        {
            SDL_Log("Failed to load texture file %s", fileName.c_str());
            return nullptr;
        }

        tex = SDL_CreateTextureFromSurface(mRenderer, surf);
        SDL_FreeSurface(surf);

        if (!tex)
        {
            SDL_Log("Failed to convert surface to texture for %s", fileName.c_str());
            return nullptr;
        }
        mTextures.emplace(fileName.c_str(), tex);
    }
    SDL_Log("Load: %s", fileName.c_str());
    return tex;
}

void Game::LoadData()
{
    mShip = new Ship(this);
    mShip->SetPosition(Vector2(512.0f, 384.0f));
    mShip->SetRotation(Math::PiOver2);

    const int numAsteroids = 20;
    for (int i = 0; i < numAsteroids; i++)
    {
        new Asteroid(this);
    }
}


void Game::UnloadData()
{
    while (!mActors.empty())
    {
        delete mActors.back();
    }

    for (auto i : mTextures)
    {
        SDL_DestroyTexture(i.second);
    }
    mTextures.clear();
}
