#include "Actor.h"
#include "Game.h"
#include "Component.h"
#include <algorithm>

Actor::Actor(Game *game)
:mState(EActive)
,mPosition(Vector2::Zero)
,mScale(1.0f)
,mRotation(0.0f)
,mGame(game)
{
    mGame->AddActor(this);
}

Actor::~Actor()
{
    mGame->RemoveActor(this);

    while (!mComponents.empty())
    {
        delete mComponents.back();
    }
}

void Actor::Update(float deltaTime)
{
    if (mState == EActive)
    {
        UpdateComponents(deltaTime);
        UpdateActor(deltaTime);
    }
}

void Actor::UpdateComponents(float deltaTime)
{
    for (auto comp : mComponents)
    {
        comp->Update(deltaTime);
    }
}

void Actor::UpdateActor(float deltaTime)
{

}

void Actor::AddComponent(Component *component)
{
    int myOrder = component->GetUpdateOrder();

    auto it = mComponents.begin();

    for (; it != mComponents.end(); it++)
    {
        if (myOrder < (*it)->GetUpdateOrder()) break;
    }

    mComponents.insert(it, component);
}

void Actor::RemoveComponent(Component *component)
{
    auto it = std::find(mComponents.begin(), mComponents.end(), component);
    if (it != mComponents.end())
    {
        mComponents.erase(it);
    }
}

