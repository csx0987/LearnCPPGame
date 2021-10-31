#include "AnimSpriteComponent.h"
#include "MathTool.h"

AnimSpriteComponent::AnimSpriteComponent(Actor *owner, int drawOrder)
:SpriteComponent(owner, drawOrder)
,mCurrFrame(0.0f)
,mAnimFPS(24.0f)
{
}

void AnimSpriteComponent::Update(float deltaTime)
{
    SpriteComponent::Update(deltaTime);

    // if (mAnimTextures.size() > 0)
    // {
    //     mCurrFrame += mAnimFPS * deltaTime;

    //     while (mCurrFrame > mAnimTextures.size())
    //     {
    //         mCurrFrame -= mAnimTextures.size();
    //     }

    //     SetTexture(mAnimTextures[static_cast<int>(mCurrFrame)]);
    // }

    // const std::vector<SDL_Texture*> animTextures = mAnimation[mCurrAnimName];
    const Animation &ani = mAnimation[mCurrAnimName];
    // if (animTextures.size() > 0)
    // {
    //     mCurrFrame += mAnimFPS * deltaTime;

    //     while (mCurrFrame > animTextures.size())
    //     {
    //         mCurrFrame -= animTextures.size();
    //     }
    //     SetTexture(animTextures[static_cast<int>(mCurrFrame)]);
    // }
    if (ani.textures.size() > 0)
    {
        mCurrFrame += mAnimFPS * deltaTime;

        if (mCurrFrame > ani.textures.size() && !ani.isLoop) {
            mCurrFrame = ani.textures.size() - 1;
        }

        while (mCurrFrame >= ani.textures.size())
        {
            mCurrFrame -= ani.textures.size();
        }

        SetTexture(ani.textures[static_cast<int>(mCurrFrame)]);

    }
}

void AnimSpriteComponent::SetAnimTextures(const std::vector<SDL_Texture*> &textures)
{
    mAnimTextures = textures;
    if (mAnimTextures.size() > 0)
    {
        mCurrFrame = 0.0f;
        SetTexture(mAnimTextures[0]);
    }
}

void AnimSpriteComponent::SetAnimation(const std::string animName, const std::vector<SDL_Texture*> &textures, const bool isLoop)
{
    // mAnimation[animName] = textures;
    mAnimation[animName] = {
        textures,
        isLoop
    };
}

void AnimSpriteComponent::PlayAnim(std::string animName)
{
    // const std::vector<SDL_Texture*> &animTextures = mAnimation[mCurrAnimName];
    const Animation &ani = mAnimation[animName];

    if (mCurrAnimName == animName) {
        if (ani.isLoop) return;
        if (static_cast<int>(mCurrFrame) < ani.textures.size() - 1) return;
    }
    // if (animTextures.size() > 0)
    // {
    //     mCurrFrame = 0.0f;
    //     SetTexture(animTextures[0]);
    // }
    mCurrAnimName = animName;
    if (ani.textures.size() > 0)
    {
        mCurrFrame = 0.0f;
        SetTexture(ani.textures[0]);
    }
}
