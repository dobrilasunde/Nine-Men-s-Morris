#include"TextSpriteComponent.hpp"
#include"Actor.hpp"

TextSpriteComponent::TextSpriteComponent(Actor* owner, int drawOrder) : SpriteComponent(owner, drawOrder) {}

void TextSpriteComponent::Draw(SDL_Renderer* renderer)
{

	SDL_Rect r;
	r.w = static_cast<int>(mScreenSize.x);
	r.h = static_cast<int>(mScreenSize.y);
	r.x = static_cast<int>(mOwner->GetPosition().x - r.w / 2);
	r.y = static_cast<int>(mOwner->GetPosition().y + 0.25*r.h);
	SDL_RenderCopy(renderer, mTexture, nullptr, &r);
}

void TextSpriteComponent::Update(float deltaTime)
{

}

void TextSpriteComponent::SetTextTexture(SDL_Texture* texture)
{
	if (mTexture != nullptr)
	{
		Free();
	}
	mTexture = texture;
	SetTexture(texture);
}

void TextSpriteComponent::Free()
{
	SDL_DestroyTexture(mTexture);
	mTexture = NULL;
	Vector2 mScreenSize = Vector2::Zero;
}