#pragma once
#include <vector>
#include "MathTool.h"

class Actor
{
public:

    enum State
    {
        EActive,
        EPaused,
        EDead
    };

    Actor(class Game *game);
    virtual ~Actor();

    void Update(float deltaTime);
    void UpdateComponents(float deltaTime);
    virtual void UpdateActor(float deltaTime);

    // 调用组件的 输入处理， 调用自己的输入处理
    void ProcessInput(const uint8_t *keyState);

    // 每个游戏对象自己的特殊输入处理
    virtual void ActorInput(const uint8_t *keyState);

    // Getter Setter
    const Vector2& GetPosition() const { return mPosition; }
	void SetPosition(const Vector2& pos) { mPosition = pos; }
	float GetScale() const { return mScale; }
	void SetScale(float scale) { mScale = scale; }
	float GetRotation() const { return mRotation; }
	void SetRotation(float rotation) { mRotation = rotation; }

    Vector2 GetForward() const { return Vector2(Math::Cos(mRotation), -Math::Sin(mRotation)); }

	State GetState() const { return mState; }
	void SetState(State state) { mState = state; }

    class Game* GetGame() { return mGame; }


    void AddComponent(class Component* component);
    void RemoveComponent(class Component* component);

private:
    State mState;

    // Transform
    Vector2 mPosition;
    float mScale;
    float mRotation;

    std::vector<class Component*> mComponents;
    class Game* mGame;
};

