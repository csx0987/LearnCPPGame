#include "Ship.h"
#include "SpriteComponent.h"
#include "InputComponent.h"
#include "Game.h"
#include "Laser.h"
#include "CircleComponent.h"
#include "Asteroid.h"

Ship::Ship(Game *game)
:Actor(game)
,mLaserCooldown(0.0f)
{
    SpriteComponent *sc = new SpriteComponent(this, 150);
    sc->SetTexture(game->GetTexture("../Assets/Ship.png"));

    InputComponent *ic = new InputComponent(this);
    ic->SetForwardKey(SDL_SCANCODE_W);
    ic->SetBackKey(SDL_SCANCODE_S);
    ic->SetClockwiseKey(SDL_SCANCODE_A);
    ic->SetCounterClockwiseKey(SDL_SCANCODE_D);
    // ic->SetMaxForwardSpeed(300.0f);
    ic->SetMaxForceValue(100.0f);
    ic->SetMaxAngularSpeed(Math::TwoPi);
    ic->SetMaxSpeed(300.0f);

    mCircle = new CircleComponent(this);
    mCircle->SetRadius(11.0f);
}

Ship::~Ship()
{
    GetGame()->ClearShip();
}

void Ship::UpdateActor(float deltaTime)
{
    mLaserCooldown -= deltaTime;

    Game *game = GetGame();

    auto asteroids = game->GetAsteroids();

    for (auto ast : asteroids)
    {
        if (Intersect(*mCircle, *(ast->GetCircle())))
        {
            SetState(EDead);
            break;
        }
    }
}

void Ship::ActorInput(const uint8_t *keyState)
{
    if (keyState[SDL_SCANCODE_SPACE] && mLaserCooldown <= 0.0f)
    {
        Laser *laser = new Laser(GetGame());
        laser->SetPosition(GetPosition());
        laser->SetRotation(GetRotation());
        laser->AddForce(GetForward() * 2000000.0f);

        mLaserCooldown = 0.5f;
    }
}
