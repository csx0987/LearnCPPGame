#pragma once
#include "Actor.h"

class Ship : public Actor
{
public:
    Ship(class Game *game);
    ~Ship();

    void UpdateActor(float deltaTime) override;
    void ActorInput(const uint8_t *state) override;
private:
    float mLaserCooldown;
    
    class CircleComponent *mCircle;
};