#include"Board.hpp"
#include<iostream>

void Board::InitializePositions()
{
	mCoordinates.insert(std::make_pair("a1", Vector2(mScreenSize.x / 2.0f - 230, mScreenSize.y / 2 +230)));
	mCoordinates.insert(std::make_pair("a4", Vector2(mScreenSize.x / 2.0f - 230, mScreenSize.y / 2)));
	mCoordinates.insert(std::make_pair("a7", Vector2(mScreenSize.x / 2.0f - 230, mScreenSize.y / 2 -230)));

	mCoordinates.insert(std::make_pair("b2", Vector2(mScreenSize.x / 2.0f - 160, mScreenSize.y / 2 + 160)));
	mCoordinates.insert(std::make_pair("b4", Vector2(mScreenSize.x / 2.0f - 160, mScreenSize.y / 2)));
	mCoordinates.insert(std::make_pair("b6", Vector2(mScreenSize.x / 2.0f - 160, mScreenSize.y / 2 - 160)));

	mCoordinates.insert(std::make_pair("c3", Vector2(mScreenSize.x / 2.0f - 90, mScreenSize.y / 2 + 85)));
	mCoordinates.insert(std::make_pair("c4", Vector2(mScreenSize.x / 2.0f - 90, mScreenSize.y / 2)));
	mCoordinates.insert(std::make_pair("c5", Vector2(mScreenSize.x / 2.0f - 90, mScreenSize.y / 2 - 85)));

	mCoordinates.insert(std::make_pair("d1", Vector2(mScreenSize.x / 2.0f, mScreenSize.y / 2 + 230)));
	mCoordinates.insert(std::make_pair("d2", Vector2(mScreenSize.x / 2.0f, mScreenSize.y / 2 + 160)));
	mCoordinates.insert(std::make_pair("d3", Vector2(mScreenSize.x / 2.0f, mScreenSize.y / 2 + 85)));
	mCoordinates.insert(std::make_pair("d5", Vector2(mScreenSize.x / 2.0f, mScreenSize.y / 2 - 85)));
	mCoordinates.insert(std::make_pair("d6", Vector2(mScreenSize.x / 2.0f, mScreenSize.y / 2 - 160)));
	mCoordinates.insert(std::make_pair("d7", Vector2(mScreenSize.x / 2.0f, mScreenSize.y / 2 - 230)));

	mCoordinates.insert(std::make_pair("e3", Vector2(mScreenSize.x / 2.0f + 90, mScreenSize.y / 2 + 85)));
	mCoordinates.insert(std::make_pair("e4", Vector2(mScreenSize.x / 2.0f + 90, mScreenSize.y / 2)));
	mCoordinates.insert(std::make_pair("e5", Vector2(mScreenSize.x / 2.0f + 90, mScreenSize.y / 2 - 85)));

	mCoordinates.insert(std::make_pair("f2", Vector2(mScreenSize.x / 2.0f + 160, mScreenSize.y / 2 + 160)));
	mCoordinates.insert(std::make_pair("f4", Vector2(mScreenSize.x / 2.0f + 160, mScreenSize.y / 2)));
	mCoordinates.insert(std::make_pair("f6", Vector2(mScreenSize.x / 2.0f + 160, mScreenSize.y / 2 - 160)));

	mCoordinates.insert(std::make_pair("g1", Vector2(mScreenSize.x / 2.0f + 230, mScreenSize.y / 2 + 230)));
	mCoordinates.insert(std::make_pair("g4", Vector2(mScreenSize.x / 2.0f + 230, mScreenSize.y / 2)));
	mCoordinates.insert(std::make_pair("g7", Vector2(mScreenSize.x / 2.0f + 230, mScreenSize.y / 2 - 230)));

}

void Board::ClearBoard()
{
	std::map<std::string, Vector2>::iterator iter;
	for (iter = mCoordinates.begin(); iter != mCoordinates.end(); iter++)
	{
		mBoard.insert(std::make_pair (iter->first, 0));
	}
}

void Board::SetStateAtPosition(std::string position, int state)
{
	mBoard.at(position) = state;
}

void Board::AddPiece(std::string position, Piece* piece)
{
	mPieces.insert(std::make_pair(position, piece));
}

void Board::RemovePiece(std::string position)
{
	mPieces.erase(position);
}

Piece* Board::GetPieceAtPosition(std::string position)
{
	return mPieces.at(position);
}

void Board::MovePiece(Piece* piece, std::string to)
{
	RemovePiece(piece->GetPositionOnBoard());
	AddPiece(to, piece);
	piece->SetPositionOnBoard(to);
}

bool Board::CheckMill(std::string position, int ID)
{
	if (position == "a1")
	{
		return (IsMill("a4", "a7", ID) || IsMill("d1", "g1", ID));
	}
	else if (position == "a4")
	{
		return(IsMill("a1", "a7", ID) || IsMill("b4", "c4", ID));
	}
	else if (position == "a7")
	{
		return(IsMill("a1", "a4", ID) || IsMill("b4", "c4", ID));
	}
	else if (position == "b2")
	{
		return(IsMill("b4", "b6", ID) || IsMill("d2", "f2", ID));
	}
	else if (position == "b4")
	{
		return(IsMill("b2", "b6", ID) || IsMill("a4", "c4", ID));
	}
	else if (position == "b6")
	{
		return(IsMill("b2", "b4", ID) || IsMill("d6", "f6", ID));
	}
	else if (position == "c3")
	{
		return(IsMill("c4", "c5", ID) || IsMill("d3", "e3", ID));
	}
	else if (position == "c4")
	{
		return(IsMill("c3", "c5", ID) || IsMill("a4", "b4", ID));
	}
	else if (position == "c5")
	{
		return(IsMill("c3", "c4", ID) || IsMill("d5", "e5", ID));
	}
	else if (position == "d1")
	{
		return(IsMill("d2", "d3", ID) || IsMill("a1", "g1", ID));
	}
	else if (position == "d2")
	{
		return(IsMill("d1", "d3", ID) || IsMill("b2", "f2", ID));
	}
	else if (position == "d3")
	{
		return(IsMill("d1", "d2", ID) || IsMill("c3", "e3", ID));
	}
	else if (position == "d5")
	{
		return(IsMill("d6", "d7", ID) || IsMill("c5", "e5", ID));
	}
	else if (position == "d6")
	{
		return(IsMill("d5", "d7", ID) || IsMill("b6", "f6", ID));
	}
	else if (position == "d7")
	{
		return(IsMill("d5", "d6", ID) || IsMill("a7", "g7", ID));
	}
	else if (position == "e3")
	{
		return(IsMill("e4", "e5", ID) || IsMill("c3", "d3", ID));
	}
	else if (position == "e4")
	{
		return(IsMill("e3", "e5", ID) || IsMill("f4", "g4", ID));
	}
	else if (position == "e5")
	{
		return(IsMill("e3", "e4", ID) || IsMill("c5", "d5", ID));
	}
	else if (position == "f2")
	{
		return(IsMill("f4", "f6", ID) || IsMill("b2", "d2", ID));
	}
	else if (position == "f4")
	{
		return(IsMill("f2", "f6", ID) || IsMill("e4", "g4", ID));
	}
	else if (position == "f6")
	{
		return(IsMill("f2", "f4", ID) || IsMill("b6", "d6", ID));
	}
	else if (position == "g1")
	{
		return(IsMill("g4", "g7", ID) || IsMill("a1", "d1", ID));
	}
	else if (position == "g4")
	{
		return(IsMill("g1", "g7", ID) || IsMill("e4", "f4", ID));
	}
	else if (position == "g7")
	{
		return(IsMill("g1", "g4", ID) || IsMill("a7", "d7", ID));
	}

	return false;
}

std::vector<std::string> Board::GetNeighbours(std::string position)
{
	std::vector<std::string> neighbours;
	if (position == "a1")
	{
		neighbours.push_back("a4");
		neighbours.push_back("d1");
	}
	else if (position == "a4")
	{
		neighbours.push_back("b4");
		neighbours.push_back("a1");
		neighbours.push_back("a7");
	}
	else if (position == "a7")
	{
		neighbours.push_back("a4");
		neighbours.push_back("d7");
	}
	else if (position == "b2")
	{
		neighbours.push_back("b4");
		neighbours.push_back("d2");
	}
	else if (position == "b4")
	{
		neighbours.push_back("b2");
		neighbours.push_back("b6");
		neighbours.push_back("a4");
		neighbours.push_back("c4");
	}
	else if (position == "b6")
	{
		neighbours.push_back("b4");
		neighbours.push_back("d6");
	}
	else if (position == "c3")
	{
		neighbours.push_back("c4");
		neighbours.push_back("d3");
	}
	else if (position == "c4")
	{
		neighbours.push_back("c3");
		neighbours.push_back("c5");
		neighbours.push_back("b4");
	}
	else if (position == "c5")
	{
		neighbours.push_back("d5");
		neighbours.push_back("c4");
	}
	else if (position == "d1")
	{
		neighbours.push_back("a1");
		neighbours.push_back("g1");
		neighbours.push_back("d2");
	}
	else if (position == "d2")
	{
		neighbours.push_back("d1");
		neighbours.push_back("d3");
		neighbours.push_back("b2");
		neighbours.push_back("f2");
	}
	else if (position == "d3")
	{
		neighbours.push_back("c3");
		neighbours.push_back("e3");
		neighbours.push_back("d2");
	}
	else if (position == "d5")
	{
		neighbours.push_back("d6");
		neighbours.push_back("c5");
		neighbours.push_back("e5");
	}
	else if (position == "d6")
	{
		neighbours.push_back("d5");
		neighbours.push_back("d7");
		neighbours.push_back("b6");
		neighbours.push_back("f6");
	}
	else if (position == "d7")
	{
		neighbours.push_back("d6");
		neighbours.push_back("g7");
		neighbours.push_back("a7");
	}
	else if (position == "e3")
	{
		neighbours.push_back("e4");
		neighbours.push_back("d3");
	}
	else if (position == "e4")
	{
		neighbours.push_back("e3");
		neighbours.push_back("e5");
		neighbours.push_back("f4");
	}
	else if (position == "e5")
	{
		neighbours.push_back("e4");
		neighbours.push_back("d5");
	}
	else if (position == "f2")
	{
		neighbours.push_back("f4");
		neighbours.push_back("d2");
	}
	else if (position == "f4")
	{
		neighbours.push_back("f2");
		neighbours.push_back("f6");
		neighbours.push_back("e4");
		neighbours.push_back("g4");
	}
	else if (position == "f6")
	{
		neighbours.push_back("f4");
		neighbours.push_back("d6");
	}
	else if (position == "g1")
	{
		neighbours.push_back("g4");
		neighbours.push_back("d1");
	}
	else if (position == "g4")
	{
		neighbours.push_back("g1");
		neighbours.push_back("g7");
		neighbours.push_back("f4");
	}
	else if (position == "g7")
	{
		neighbours.push_back("g4");
		neighbours.push_back("d7");
	}

	return neighbours;
}

bool Board::CheckJump(std::string position1, std::string position2)
{
	std::vector<std::string> neighbours = GetNeighbours(position1);

	if (!neighbours.empty())
	{
		for (int i = 0; i < neighbours.size(); ++i)
		{
			if (neighbours[i] == position2)
			{
				return true;
			}
		}
		return false;
	}
	return false;
}

bool Board::IsMill(std::string position1, std::string position2, int ID)
{
	if (GetStateAtPosition(position1) == ID && GetStateAtPosition(position2) == ID)
	{
		return true;
	}
	return false;
}

bool Board::CheckIfMovesAvailable(int ID)
{
	std::map<std::string, int>::iterator iter;
	for (iter = mBoard.begin(); iter != mBoard.end(); iter++)
	{
		if (iter->second == ID)
		{
			std::vector<std::string> neighbours = GetNeighbours(iter->first);
			for (int i = 0; i < neighbours.size(); ++i)
			{
				if (GetStateAtPosition(neighbours[i]) == 0)
				{
					return true;
				}
			}
		}
	}

	return false;
}
