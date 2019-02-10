#pragma once
#include"Actor.hpp"
#include"PieceSpriteComponent.hpp"
#include"MoveComponent.hpp"

class Piece : public Actor
{
public:
	enum State { PLACED, NOTPLACED, EATEN };

	Piece(Game *game, int Color);	
	~Piece();
	bool PlacePiece(Vector2 coordinates, std::string);
	bool EatPiece();
	State GetCurrentState() { return mCurrentState; }
	void SetCurrentState(State state) { mCurrentState = state; }
	std::string GetPositionOnBoard() { return mPositionOnBoard; }
	void SetPositionOnBoard(std::string position) { mPositionOnBoard = position; }
	void Move(Vector2 to);

private:
	State mCurrentState;
	std::string mPositionOnBoard;
	class PieceSpriteComponent *mPiece;
	int mColor;
	class MoveComponent* mMoveComponent;
};