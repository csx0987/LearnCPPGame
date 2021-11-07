#pragma once
#include "MoveComponent.h"
#include <cstdint>

class InputComponent: public MoveComponent
{
public:
    InputComponent(class Actor *owner);

    void ProcessInput(const uint8_t *keyState) override;

    // Getters/setters for private variables
	// float GetMaxForward() const { return mMaxForwardSpeed; }
	float GetMaxForceValue() const { return mMaxForceValue; }
	float GetMaxAngular() const { return mMaxAngularSpeed; }
	int GetForwardKey() const { return mForwardKey; }
	int GetBackKey() const { return mBackKey; }
	int GetClockwiseKey() const { return mClockwiseKey; }
	int GetCounterClockwiseKey() const { return mCounterClockwiseKey; }

	// void SetMaxForwardSpeed(float speed) { mMaxForwardSpeed = speed; }
	void SetMaxForceValue(float value) { mMaxForceValue = value; }
	void SetMaxAngularSpeed(float speed) { mMaxAngularSpeed = speed; }
	void SetForwardKey(int key) { mForwardKey = key; }
	void SetBackKey(int key) { mBackKey = key; }
	void SetClockwiseKey(int key) { mClockwiseKey = key; }
	void SetCounterClockwiseKey(int key) { mCounterClockwiseKey = key; }

private:

    // float mMaxForwardSpeed;
	float mMaxForceValue;
    float mMaxAngularSpeed;

    int mForwardKey;
    int mBackKey;

    int mClockwiseKey;
    int mCounterClockwiseKey;

};