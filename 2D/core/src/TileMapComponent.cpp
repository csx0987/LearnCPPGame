#include <SDL_rwops.h>
#include "Actor.h"
#include "TileMapComponent.h"
#include "MathTool.h"

TileMapComponent::TileMapComponent(Actor *owner, int drawOrder)
:SpriteComponent(owner, drawOrder)
,row(0)
,col(0)
{

}

void TileMapComponent::SetTexture(SDL_Texture *texture)
{
    SpriteComponent::SetTexture(texture);
    row = mTexHeight / 32;
    col = mTexWidth / 32;

    SDL_Log("row: %d col: %d", row, col);
}

void TileMapComponent::Draw(SDL_Renderer *renderer)
{
    if (tileIndexs.size() > 0 && mTexture)
    {
        int edge = 32;
        // SDL_Log("w: %d h: %d edge: %d", mTexWidth, mTexHeight, edge);
        SDL_Rect srcRect;
        SDL_Rect dstRect;
        for (int i = 0; i < tileIndexs.size(); i++)
        {
            int value = tileIndexs[i];
            if (value == -1) continue;
            int dstR = i / 32;
            int dstC = i % 32;
            int srcR = (value) / col;
            int srcC = (value) % col;

            srcRect.x = (srcC) * edge ;
            srcRect.y = (srcR) * edge;
            srcRect.w = edge;
            srcRect.h = edge;

            dstRect.x = (dstC) * edge;
            dstRect.y = (dstR) * edge;
            dstRect.w = edge;
            dstRect.h = edge;
            // SDL_Log("dstR: %d dstC: %d srcR: %d srcC: %d, value: %d, i: %d", dstR, dstC, srcR, srcC, value, i);

            SDL_RenderCopyEx(
                renderer,
                mTexture,
                &srcRect,
                &dstRect,
                // nullptr,
                -Math::ToDegrees(mOwner->GetRotation()),
                nullptr,
                SDL_FLIP_NONE
            );
            // break;
        }

    }
}

void TileMapComponent::LoadTile(std::string fileName)
{
    size_t *dataSize = new size_t();
    char *pt = static_cast<char*>(SDL_LoadFile(fileName.c_str(), dataSize));
    char *p = pt;

    if (p != nullptr)
    {
        tileIndexs.clear();
    }
    else
    {
        SDL_Log("failed to load file %s", fileName.c_str());
    }

    int tmp = 0;
    bool isNeg = false;
    int cnt = 0;
    while (*p != 0)
    {
        char ch = *p;
        if (ch == '\n' || ch == '\r' || ch ==',')
        {
            if (isNeg) tmp = -tmp;
            tileIndexs.push_back(tmp);
            tmp = 0;
            isNeg = false;
            cnt++;
            if (ch != ',')
            {
                cnt = 0;
            }
        }
        else if (ch == '-')
        {
            isNeg = true;
        }
        else
        {
            tmp *= 10;
            tmp += (*p) - '0';
        }
        p++;
    }

    SDL_Log("file %s size: %zu", fileName.c_str(), *dataSize);

    delete dataSize;
    SDL_free(pt);
}