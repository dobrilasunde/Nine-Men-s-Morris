#include"Piece.hpp"
#include"Game.hpp"
#include"MoveComponent.hpp"
#include<iostream>
Piece::Piece(Game* game, int color) : Actor(game), mPiece(nullptr), mCurrentState(State::NOTPLACED), mColor(color)
{

	mMoveComponent = new MoveComponent(this);
	mMoveComponent->SetForwardSpeed(100.0f);

}

bool Piece::PlacePiece(Vector2 coordinates, std::string position)
{
	SetPosition(coordinates);
	mMoveComponent->SetFrom(GetPosition());
	mMoveComponent->SetTo(GetPosition());


	if (mCurrentState == PLACED || mCurrentState == EATEN)
	{
		return false;
	}
	PieceSpriteComponent* piece = new PieceSpriteComponent(this, mColor, 70);
	piece->SetPieceSize(30);
	SetCurrentState(State::PLACED);

	mPositionOnBoard = position;
	return true;
}

bool Piece::EatPiece()
{
	this->SetCurrentState(EATEN);
	this->SetState(EDead);

	return true;
}

Piece::~Piece()
{
}

void Piece::Move(Vector2 to)
{
	mMoveComponent->SetFrom(GetPosition());
	mMoveComponent->SetTo(to);
}
