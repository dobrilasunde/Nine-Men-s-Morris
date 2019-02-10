#include"BGSpriteComponent.hpp"
#include"Actor.hpp"

BGSpriteComponent::BGSpriteComponent(class Actor* owner, int drawOrder) : SpriteComponent(owner, drawOrder) {}

void BGSpriteComponent::Update(float deltaTime)
{
}

void BGSpriteComponent::Draw(SDL_Renderer* renderer)
{
	for (auto tex : mBGTexture)
	{
		SDL_Rect r;
		r.w = static_cast<int>(mScreenSize.x);
		r.h = static_cast<int>(mScreenSize.y);
		r.x = static_cast<int>(mOwner->GetPosition().x - r.w / 2);
		r.y = static_cast<int>(mOwner->GetPosition().y - r.h / 2);

		SDL_RenderCopy(renderer, tex, nullptr, &r);
	}
		
}

void BGSpriteComponent::SetBGTexture(const std::vector<SDL_Texture*>& textures)
{
	int count = 0;
	for (auto tex : textures)
	{
		SDL_Texture* temp;
		temp = tex;
		mBGTexture.emplace_back(temp);
		count++;
	}

}


