#include "MoveComponent.h"
#include "Actor.h"

MoveComponent::MoveComponent(class Actor *owner, int updateOrder)
:Component(owner, updateOrder)
,mAngularSpeed(0.0f)
// ,mForwardSpeed(0.0f)
,mForwardSpeed(Vector2::Zero)
,mForce(Vector2::Zero)
,mMass(1.0f)
,mMaxSpeed(0.0f)
{

}

void MoveComponent::Update(float deltaTime)
{
    if (!Math::NearZero(mAngularSpeed))
    {
        float rot = mOwner->GetRotation();
        rot += mAngularSpeed * deltaTime;
        mOwner->SetRotation(rot);
    }

    // 计算速度
    if (!Math::NearZero(mForce))
    {
        Vector2 a = mForce / mMass;
        mForwardSpeed += a * deltaTime;
        if (mForwardSpeed.LengthSq() >= mMaxSpeed * mMaxSpeed) {
            mForwardSpeed.Normalize();
            mForwardSpeed *= mMaxSpeed;
        }
    }

    if (!Math::NearZero(mForwardSpeed))
    {
        Vector2 pos = mOwner->GetPosition();
        // pos += mOwner->GetForward() * mForwardSpeed * deltaTime;
        pos += mForwardSpeed * deltaTime;

        if (pos.x < 0.0f) { pos.x = 1022.0f; }
        else if (pos.x > 1024.0f) { pos.x = 2.0f; }

        if (pos.y < 0.0f) { pos.y = 766.0f; }
        else if (pos.y > 768.0f) { pos.y = 2.0f; }

        mOwner->SetPosition(pos);
    }

    // 清空力
    if (!Math::NearZero(mForce))
    {
        mForce = Vector2::Zero;
    }
}
