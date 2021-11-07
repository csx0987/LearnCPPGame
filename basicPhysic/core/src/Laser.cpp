#include "Laser.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "Game.h"
#include "CircleComponent.h"
#include "Asteroid.h"
#include "MathTool.h"

Laser::Laser(Game *game)
:Actor(game)
,mDeathTimer(1.0f)
,mMove(nullptr)
{
    SpriteComponent *sc = new SpriteComponent(this);
    sc->SetTexture(game->GetTexture("../Assets/Laser.png"));


    MoveComponent *mc = new MoveComponent(this);
    mc->SetMass(1);
    // mc->SetForwardSpeed(GetForward() * 800.0f);
    mc->SetMaxSpeed(800.0f);

    mMove = mc;

    mCircle = new CircleComponent(this);
    mCircle->SetRadius(11.0f);
}

void Laser::AddForce(const Vector2 &v)
{
    if (mMove != nullptr)
    {
        mMove->AddForce(v);
    }
}

void Laser::UpdateActor(float deltaTime)
{
    mDeathTimer -= deltaTime;
    if (mDeathTimer <= 0.0f)
    {
        SetState(EDead);
    }
    else
    {
        for (auto ast : GetGame()->GetAsteroids())
        {
            if (Intersect(*mCircle, *(ast->GetCircle())))
            {
                SetState(EDead);
                ast->SetState(EDead);
                break;
            }
        }
    }
}
