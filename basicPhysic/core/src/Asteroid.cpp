#include "Asteroid.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "Game.h"
#include "Random.h"
#include "CircleComponent.h"

Asteroid::Asteroid(Game *game)
: Actor(game)
{
    Vector2 randPos = Random::GetVector(Vector2::Zero, Vector2(1024.0f, 768.0f));
    SetPosition(randPos);

    SetRotation(Random::GetFloatRange(0.0f, Math::TwoPi));

    SpriteComponent *sc = new SpriteComponent(this);
    sc->SetTexture(game->GetTexture("../Assets/Asteroid.png"));

    MoveComponent *mc = new MoveComponent(this);
    // mc->SetForwardSpeed(150.0f);
    mc->SetMass(1);
    mc->AddForce(mc->GetForward() * 150000.0f);
    mc->SetMaxSpeed(150.0f);

    // 包围盒
    mCircle = new CircleComponent(this);
    mCircle->SetRadius(40.0f);


    game->AddAsteroid(this);    
}

Asteroid::~Asteroid()
{
    GetGame()->RemoveAsteroid(this);
}
