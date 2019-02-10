#pragma once
#include"SpriteComponent.hpp"
#include<vector>
#include"Math.hpp"

class PieceSpriteComponent : public SpriteComponent
{
public:
	PieceSpriteComponent(Actor* owner, int color, int drawOrder = 20);
	void Update(float deltaTime) override;
	void Draw(SDL_Renderer *renderer) override;
	void SetPieceSize(float radius) { mRadius = radius; }

private:
	float mRadius;
	int mColor;
};