#pragma once
#include <cstdint>

class Component
{
protected:
    class Actor *mOwner;
    int mUpdateOrder;

public:
    Component(class Actor* owner, int updateOrder = 100);
    virtual ~Component();

    virtual void Update(float deltaTime);

    // 每一个组件在处理输入阶段被调用
    virtual void ProcessInput(const uint8_t *keyState) {}

    int GetUpdateOrder() const { return mUpdateOrder; }
};
