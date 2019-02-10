#pragma once
#include"SpriteComponent.hpp"
#include<vector>
#include"Math.hpp"

class TextSpriteComponent : public SpriteComponent
{
public:
	TextSpriteComponent(class Actor* actor, int drawOrder = 200);
	void Update(float deltaTime) override;
	void Draw(SDL_Renderer *renderer) override;
	void SetTextTexture(SDL_Texture* texture);
	void SetScreenSize(const Vector2& size) { mScreenSize = size; }
	void Free();

private:
	SDL_Texture* mTextTexture;
	Vector2 mScreenSize;
};