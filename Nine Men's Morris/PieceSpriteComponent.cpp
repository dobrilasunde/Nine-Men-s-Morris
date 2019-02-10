#include"PieceSpriteComponent.hpp"
#include"Actor.hpp"
#include<iostream>

PieceSpriteComponent::PieceSpriteComponent(Actor* owner, int color, int drawOrder) : SpriteComponent(owner, drawOrder), mColor(color) {}

void PieceSpriteComponent::Draw(SDL_Renderer* renderer)
{

	if (mColor == 1)
	{
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	}
	else if(mColor == 2)
	{
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	}
	else
	{
		SDL_SetRenderDrawColor(renderer, 11, 110, 79, 255);
	}
	for (int w = 0; w < mRadius * 2; w++)
	{
		for (int h = 0; h < mRadius * 2; h++)
		{
			int dx = mRadius - w;
			int dy = mRadius - h;
			if ((dx*dx + dy*dy) <= (mRadius * mRadius))
			{
				SDL_RenderDrawPoint(renderer, mOwner->GetPosition().x + dx, mOwner->GetPosition().y + dy);
			}
		}
	}
}

void PieceSpriteComponent::Update(float deltaTime)
{

}