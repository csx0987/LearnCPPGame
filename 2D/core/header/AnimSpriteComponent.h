#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include "SpriteComponent.h"

struct Animation
{
    std::vector<SDL_Texture*> textures;
    bool isLoop;
};

class AnimSpriteComponent : public SpriteComponent
{
public:
    AnimSpriteComponent(class Actor *owner, int drawOrder = 100);

    virtual void Update(float deltaTime) override;
    void SetAnimTextures(const std::vector<SDL_Texture*> &textures);
    void SetAnimation(const std::string animName, const std::vector<SDL_Texture*> &textures, const bool isLoop = false);
    void PlayAnim(std::string animName);
    
    float GetAnimFPS() const { return mAnimFPS; }
    void SetAnimFPS(float fps) { mAnimFPS = fps; }

private:
    std::string mCurrAnimName;
    std::unordered_map<std::string, Animation> mAnimation;
    float mCurrFrame;
    float mAnimFPS;
};
