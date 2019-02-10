#include"MoveComponent.hpp"
#include"Actor.hpp"
#include<iostream>
#include<math.h>
MoveComponent::MoveComponent(class Actor* owner, int updateOrder) : Component(owner, updateOrder), mForwardSpeed(0.0f), mTo(owner->GetPosition()), mFrom(owner->GetPosition())
{

}

void MoveComponent::Update(float deltaTime)
{
	if (!Math::NearZero(mForwardSpeed))
	{
		Vector2 pos = mOwner->GetPosition();

		if (pos.x >= mFrom.x && pos.x < mTo.x)
		{
			pos.x += mForwardSpeed * deltaTime;
		}
		if (pos.x <= mFrom.x && pos.x > mTo.x)
		{
			pos.x -= mForwardSpeed * deltaTime;
		}

		if (pos.y >= mFrom.y && pos.y < mTo.y)
		{
			pos.y += mForwardSpeed * deltaTime;
		}
		if (pos.y <= mFrom.y && pos.y > mTo.y)
		{
			pos.y -= mForwardSpeed * deltaTime;
		}

		mOwner->SetPosition(pos);

	}
}