#pragma once
#include "Component.hpp"
#include"Math.hpp"
class MoveComponent : public Component
{
public:
	MoveComponent(class Actor* owner, int updateOrder = 10);

	void Update(float deltaTime) override;

	float GetForwardSpeed() const { return mForwardSpeed; }
	void SetForwardSpeed(float speed) { mForwardSpeed = speed; }
	void SetTo(Vector2 to) { mTo = to; }
	void SetFrom(Vector2 from) { mFrom = from; }

private:
	float mForwardSpeed;
	Vector2 mFrom;
	Vector2 mTo;
};