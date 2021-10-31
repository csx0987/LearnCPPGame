#include <vector>
#include <string>
#include "SpriteComponent.h"


class TileMapComponent : public SpriteComponent
{
public:
    TileMapComponent(class Actor *owner, int drawOrder = 100);
    void SetTexture(SDL_Texture *texture) override;
    void Draw(SDL_Renderer *renderer) override;
    void LoadTile(std::string fileName);

private:
    std::vector<int> tileIndexs;
    int row;
    int col;
};