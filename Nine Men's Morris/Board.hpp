#pragma once
#include"Actor.hpp"
#include<map>
#include"Math.hpp"
#include"Piece.hpp"

class Board: public Actor
{
public:

	Board(Game* game, float screenSizex, float screenSizey, float boardSizex, float boardSizey) : Actor(game), mScreenSize(Vector2(screenSizex, screenSizey)), mBoardSize(Vector2(boardSizex, boardSizey)) {}
	void InitializePositions();
	void ClearBoard();

	Vector2 GetCoordinatesAt(std::string position) { return mCoordinates.at(position); }
	int GetStateAtPosition(std::string position) { return mBoard.at(position); }
	std::map<std::string, Vector2> GetCoordinatesMap() const { return mCoordinates; }

	void SetStateAtPosition(std::string position, int state);
	class Piece* GetPieceAtPosition(std::string position);

	void AddPiece(std::string position, class Piece* piece);
	void RemovePiece(std::string position);	
	void MovePiece(Piece* piece, std::string to);
	
	bool CheckMill(std::string position, int ID);
	bool CheckJump(std::string positionFrom, std::string positionTo);
	bool CheckIfMovesAvailable(int ID);
	std::vector<std::string> GetNeighbours(std::string position);


private:
	bool IsMill(std::string position1, std::string position2, int ID);

	std::map<std::string, Vector2> mCoordinates;
	std::map<std::string, int> mBoard;
	std::map<std::string, Piece*> mPieces;

	Vector2 mScreenSize;
	Vector2 mBoardSize;
};
