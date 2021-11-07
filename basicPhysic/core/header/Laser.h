#pragma once

#include "Actor.h"

class Laser: public Actor
{
public:
    Laser(class Game *game);

    void UpdateActor(float deltaTime) override;

    void AddForce(const class Vector2 &v);

private:
    class CircleComponent *mCircle;
    float mDeathTimer;
    class MoveComponent *mMove;
};
