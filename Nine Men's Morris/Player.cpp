#include"Player.hpp"
#include<iostream>
#include"TextSpriteComponent.hpp"
#include"Game.hpp"



Player::Player(Game* game, Board& board, int ID) : Actor(game), mState(EActive), mBoard(board), mID(ID)
{
	for (int i = 0; i < mOwnedPieces; ++i)
	{
		mPieces.push_back(new Piece(game, ID));
	}

}

bool Player::PlacePiece(std::string position)
{
	if (mBoard.GetStateAtPosition(position) == 0)
	{
		if (mPieces[mCurrentlyPlacedPieces]->PlacePiece(mBoard.GetCoordinatesAt(position), position))
		{
			mBoard.AddPiece(position, mPieces[mCurrentlyPlacedPieces]);
			mCurrentlyPlacedPieces++;
			mBoard.SetStateAtPosition(position, mID);

			if (mBoard.CheckMill(position, mID))
			{
				std::cout << "MILL FOR " << mID << std::endl;
				GetGame()->SetGameState(GetGame()->EATING);
			}
			else if (mCurrentlyPlacedPieces == mOwnedPieces)
			{
				GetGame()->NotifyPlacingFinished();
				if (GetGame()->IsPlacingFinished())
				{
					GetGame()->SetGameState(GetGame()->MOVING);
				}
			}
		}
		else
		{
			std::cout << "Can't place current piece at this position." << std::endl;
		}
	}
	else
	{
		std::cout << "All pieces already used or current position unavailable" << std::endl;
		return false;
	}

	return true;
}

bool Player::EatPiece(std::string position)
{
	if (mBoard.GetStateAtPosition(position) == (3-mID))
	{
		mBoard.GetPieceAtPosition(position)->EatPiece();
		mBoard.RemovePiece(position);
		mBoard.SetStateAtPosition(position, 0);
		mEatenPieces++;
		return true;
	}
	return false;
}

bool Player::MovePiece(std::string positionFrom, std::string positionTo)
{
	if (mBoard.GetStateAtPosition(positionFrom) == mID && mBoard.GetStateAtPosition(positionTo) == 0 && mBoard.CheckJump(positionFrom, positionTo))
	{
		mBoard.GetPieceAtPosition(positionFrom)->Move(mBoard.GetCoordinatesAt(positionTo));
		mBoard.MovePiece(mBoard.GetPieceAtPosition(positionFrom), positionTo);
		mBoard.SetStateAtPosition(positionFrom, 0);
		mBoard.SetStateAtPosition(positionTo, mID);
		
		

		if (mBoard.CheckMill(positionTo, mID))
		{
			GetGame()->SetGameState(GetGame()->EATING);
		}
		
		return true;
	}
	return false;
}

void Player::UpdateActor(float deltaTime)
{
	
	if (GetGame()->GetPlayerTurn() == mID)
	{
		mState = EActive;
	}
	else
	{
		mState = EPaused;
	}
}

void Player::ActorInput(int x, int y)
{
	if (mState == EActive)
	{
		std::map<std::string, Vector2>::iterator iter;
		std::map<std::string, Vector2> coordinatesMap = mBoard.GetCoordinatesMap();

		
		for (iter = coordinatesMap.begin(); iter != coordinatesMap.end(); iter++)
		{
			if (CheckCollision(iter->second, Vector2(x, y)))
			{
				//1st phase of the game - PLACING
				if (GetGame()->GetGameState() == GetGame()->PLACING && mCurrentlyPlacedPieces < mOwnedPieces && !(GetGame()->IsPlacingFinished()))
				{
					if (PlacePiece(iter->first))
					{
						if (GetGame()->GetGameState() != GetGame()->EATING)
						{
							GetGame()->EndTurn();
						}
					}
				}

				else if (GetGame()->GetGameState() == GetGame()->EATING)
				{
					if (EatPiece(iter->first) == true)
					{
						if (mCurrentlyPlacedPieces < mOwnedPieces && !(GetGame()->IsPlacingFinished()))
						{
							GetGame()->SetGameState(GetGame()->PLACING);
						}
						else if (GetGame()->IsPlacingFinished())
						{
							GetGame()->SetGameState(GetGame()->MOVING);
						}
						else if (mCurrentlyPlacedPieces == mOwnedPieces)
						{
							GetGame()->NotifyPlacingFinished();
							if (GetGame()->IsPlacingFinished())
							{
								GetGame()->SetGameState(GetGame()->MOVING);
							}
							else
							{
								GetGame()->SetGameState(GetGame()->PLACING);
							}
						}

						GetGame()->EndTurn();
					}

				}

				//2nd phase of the game - MOVING
				else if (GetGame()->GetGameState() == GetGame()->MOVING && GetGame()->IsPlacingFinished())
				{
					if (mMovePieceFrom.empty() && mBoard.GetStateAtPosition(iter->first) == mID)
					{
						mMovePieceFrom.assign(iter->first);
						if (!mMovePieceTo.empty() && !mMovePieceFrom.empty())
						{
							if (MovePiece(mMovePieceFrom, mMovePieceTo))
							{
								mMovePieceFrom.erase();
								mMovePieceTo.erase();
								if (GetGame()->GetGameState() != GetGame()->EATING)
								{
									GetGame()->EndTurn();
								}
							}
							else
							{
								mMovePieceFrom.erase();
								mMovePieceTo.erase();
							}
						}
					}
					else if (mMovePieceTo.empty() && mBoard.GetStateAtPosition(iter->first) == 0)
					{
						mMovePieceTo.assign(iter->first);
						if (!mMovePieceTo.empty() && !mMovePieceFrom.empty())
						{
							if (MovePiece(mMovePieceFrom, mMovePieceTo))
							{
								mMovePieceFrom.erase();
								mMovePieceTo.erase();
								if (GetGame()->GetGameState() != GetGame()->EATING)
								{
									GetGame()->EndTurn();
								}
							}
							else
							{
								mMovePieceFrom.erase();
								mMovePieceTo.erase();
							}
						}
					}
				}
			}
		}
		CheckVictory();
	}

}

bool Player::CheckCollision(const Vector2& circleCenter, const Vector2& point)
{
	float diff = pow((circleCenter.x - point.x),2) + pow((circleCenter.y - point.y),2);
	float distSq = sqrt(diff);

	return distSq <= mCollisionRadius;
}



void Player::CheckVictory()
{
	if (mEatenPieces >= 7)
	{
		GetGame()->SetPlayerWon(mID);
		GetGame()->SetGameState(GetGame()->GAMEOVER);
	}

	if (GetGame()->IsPlacingFinished())
	{
		if (!mBoard.CheckIfMovesAvailable(mID))
		{
			GetGame()->SetPlayerWon(mID);
			GetGame()->SetGameState(GetGame()->GAMEOVER);
		}
	}
}

