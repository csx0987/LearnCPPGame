#pragma once

#include "Component.h"
#include "MathTool.h"
#include "Actor.h"

class MoveComponent : public Component
{
public:
    MoveComponent(class Actor *owner, int updateOrder = 10);

    void Update(float deltaTime) override;

    float GetAngularSpeed() const { return mAngularSpeed; }
    // float GetForwardSpeed() const { return mForwardSpeed; }
    const Vector2& GetForwardSpeed() const { return mForwardSpeed; }

    void SetAngularSpeed(float speed) { mAngularSpeed = speed; }
    // void SetForwardSpeed(float speed) { mForwardSpeed = speed; }
    void SetForwardSpeed(const Vector2 &speed) { mForwardSpeed = speed; }

    void SetMass(float mass) { mMass = mass; }
    void SetForce(const Vector2 &force) { mForce = force; }
    void AddForce(const Vector2 &force) { mForce += force; }

    void SetMaxSpeed(float speed) { mMaxSpeed = speed; }
    float GetMaxSpeed() { return mMaxSpeed; }

    const Vector2 GetForward() { return mOwner->GetForward(); }

private:

    float mAngularSpeed;
    // float mForwardSpeed;
    Vector2 mForwardSpeed;

    Vector2 mForce;
    float mMass;

    float mMaxSpeed;
};