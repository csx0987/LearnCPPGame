#include "Ship.h"
#include "AnimSpriteComponent.h"
#include "Game.h"

Ship::Ship(Game *game)
:Actor(game)
,mRightSpeed(0.0f)
,mDownSpeed(0.0f)
{
    AnimSpriteComponent *asc = new AnimSpriteComponent(this);
    // std::vector<SDL_Texture*> anims = {
    //     game->GetTexture("../Assets/Ship01.png"),
    //     game->GetTexture("../Assets/Ship02.png"),
    //     game->GetTexture("../Assets/Ship03.png"),
    //     game->GetTexture("../Assets/Ship04.png")
    // };
    // asc->SetAnimation("walk", anims, true);


    std::vector<SDL_Texture*> walk = {
        game->GetTexture("../Assets/Character01.png"),
        game->GetTexture("../Assets/Character02.png"),
        game->GetTexture("../Assets/Character03.png"),
        game->GetTexture("../Assets/Character04.png"),
        game->GetTexture("../Assets/Character05.png"),
        game->GetTexture("../Assets/Character06.png"),
    };

    asc->SetAnimation("walk", walk, true);

    std::vector<SDL_Texture*> jump = {
        game->GetTexture("../Assets/Character07.png"),
        game->GetTexture("../Assets/Character08.png"),
        game->GetTexture("../Assets/Character09.png"),
        game->GetTexture("../Assets/Character10.png"),
        game->GetTexture("../Assets/Character11.png"),
        game->GetTexture("../Assets/Character12.png"),
        game->GetTexture("../Assets/Character13.png"),
        game->GetTexture("../Assets/Character14.png"),
        game->GetTexture("../Assets/Character15.png"),
    };

    asc->SetAnimation("jump", jump);

    std::vector<SDL_Texture*> punch = {
        game->GetTexture("../Assets/Character16.png"),
        game->GetTexture("../Assets/Character17.png"),
        game->GetTexture("../Assets/Character18.png"),
    };

    asc->SetAnimation("punch", punch);

    asc->PlayAnim("walk");

    animSprite = asc;
}

void Ship::UpdateActor(float deltaTime)
{
    Actor::UpdateActor(deltaTime);

    Vector2 pos = GetPosition();
    pos.x += mRightSpeed * deltaTime;
    pos.y += mDownSpeed * deltaTime;

    if (pos.x < 25.0f)
    {
        pos.x = 25.0f;
    }
    else if (pos.x > 500.0f)
    {
        pos.x = 500.0f;
    }

    if (pos.y < 25.0f)
    {
        pos.y = 25.0f;
    }
    else if (pos.y > 743.0f)
    {
        pos.y = 743.0f;
    }
    SetPosition(pos);
}

void Ship::ProcessKeyboard(const uint8_t *state)
{
    mRightSpeed = 0.0f;
	mDownSpeed = 0.0f;
	// right/left
	if (state[SDL_SCANCODE_D])
	{
		mRightSpeed += 250.0f;
	}
	if (state[SDL_SCANCODE_A])
	{
		mRightSpeed -= 250.0f;
	}
	// up/down
	if (state[SDL_SCANCODE_S])
	{
		mDownSpeed += 300.0f;
	}
	if (state[SDL_SCANCODE_W])
	{
		mDownSpeed -= 300.0f;
	}

    if (state[SDL_SCANCODE_J])
    {
        animSprite->PlayAnim("walk");
    }

    if (state[SDL_SCANCODE_K])
    {
        animSprite->PlayAnim("jump");
    }

    if (state[SDL_SCANCODE_L])
    {
        animSprite->PlayAnim("punch");
    }
}
