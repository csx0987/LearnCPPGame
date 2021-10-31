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



    SDL_Texture* LoadTexture(const char *fileName);
    SDL_Texture* GetTexture(const std::string &fileName);
};