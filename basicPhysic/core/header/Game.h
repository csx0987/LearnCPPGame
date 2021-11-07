#pragma once
#include <vector>
#include <unordered_map>
#include <string>
#include <SDL.h>

class Game
{
private:
    SDL_Window *mWindow;
    SDL_Renderer *mRenderer;
    bool mIsRunning;

    Uint32 mTicksCount;

    std::vector<class Actor*> mActors;
    std::vector<class Actor*> mPendingActors;
    std::vector<class SpriteComponent*> mSprites;
    std::unordered_map<std::string, SDL_Texture*> mTextures;

    bool mUpdatingActors;

    class Ship* mShip;

    std::vector<class Asteroid*> mAsteroids;

    float mRebirthTime;

    void ProcessInput(); // 处理输入
    void UpdateGame(); // 
    void GenerateOutput();
    void LoadData();
    void UnloadData();
public:
    Game();

    bool Initialize();
    void RunLoop();
    void Shutdown();

    void AddActor(class Actor* actor);
    void RemoveActor(class Actor* actor);
    void AddSprite(class SpriteComponent* sprite);
    void RemoveSprite(class SpriteComponent* sprite);

    void AddAsteroid(class Asteroid* ast);
    void RemoveAsteroid(class Asteroid *ast);
    std::vector<class Asteroid*>& GetAsteroids() { return mAsteroids; }

    SDL_Texture* GetTexture(const std::string &fileName);

    void ClearShip() { mShip = nullptr; }
};