#pragma once
#include"SpriteComponent.hpp"
#include<vector>
#include"Math.hpp"

class BGSpriteComponent : public SpriteComponent
{
public:
	BGSpriteComponent(class Actor* actor, int drawOrder = 10);
	void Update(float deltaTime) override;
	void Draw(SDL_Renderer *renderer) override;
	void SetBGTexture(const std::vector<SDL_Texture*>& textures);
	void SetScreenSize(const Vector2& size) { mScreenSize = size; }
	
private:
	std::vector<SDL_Texture*> mBGTexture;
	Vector2 mScreenSize;
};