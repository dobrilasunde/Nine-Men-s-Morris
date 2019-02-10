#pragma once

#include"Actor.hpp"
#include"Piece.hpp"
#include"Board.hpp"

class Player : public Actor
{
public:
	Player(Game *game, Board& board, int ID);
	void UpdateActor(float deltaTime) override;
	void ActorInput(int x, int y) override;
	void SetState(State state) { mState = state; }	
	int GetCurrentlyPlacedPieces() { return mCurrentlyPlacedPieces; }
	std::string GetMovePieceFrom() { return mMovePieceFrom; }

private:
	bool PlacePiece(std::string);
	bool EatPiece(std::string position);
	bool MovePiece(std::string positionFrom, std::string positionTo);
	void CheckVictory();
	bool CheckCollision(const Vector2& circleCenter, const Vector2& point);

	std::vector<class Piece*> mPieces;
	class Board& mBoard;
	int mOwnedPieces = 9;
	int mCurrentlyPlacedPieces = 0;
	int mEatenPieces = 0;
	int mCollisionRadius = 30;
	int mID;
	State mState;
	std::string mMovePieceFrom;
	std::string mMovePieceTo;
};

