#include"Game.hpp"
#include<SDL_image.h>
#include<algorithm>
#include"Actor.hpp"
#include"SpriteComponent.hpp"
#include"BGSpriteComponent.hpp"
#include"PieceSpriteComponent.hpp"
#include<iostream>
#include"Player.hpp"
#include<SDL_ttf.h>
#include"TextSpriteComponent.hpp"
#include<sstream>
#include<Windows.h>

Game::Game(): mWindow(nullptr), mRenderer(nullptr), mIsRunning(true), mUpdatingActors(false), mState(PLACING), mPlayerTurn(1), mPlacingFinished(0), mBoard(this, 1024.0f, 768.0f, 500.0f, 500.0f), mPlayer1(nullptr), mPlayer2(nullptr) {}

bool Game::Initialize()
{

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	mWindow = SDL_CreateWindow("Nine Men's Morris", 100, 100, 1024, 768, 0);
	if (!mWindow)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}

	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!mRenderer)
	{
		SDL_Log("Failed to create renderer: %s", SDL_GetError());
		false;
	}

	if (IMG_Init(IMG_INIT_PNG) == 0)
	{
		SDL_Log("Unable to initialize SDL_image: %s", SDL_GetError());
		return false;
	}

	if (TTF_Init() < 0)
	{
		SDL_Log("Unable to initialize SDL_ttf: %s", SDL_GetError());
		return false;
	}

	LoadData();

	mTicksCount = SDL_GetTicks();

	return true;
}

void Game::Shutdown()
{
	UnloadData();
	TTF_Quit();
	IMG_Quit();
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}

void Game::RunLoop()
{
	while (mIsRunning)
	{
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}

void Game::Restart()
{
	UnloadData();
	if (!Initialize())
	{
		std::cout << "Failed" << std::endl;
	}
}

void Game::ProcessInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				mIsRunning = false;
				break;
			case SDL_MOUSEBUTTONDOWN:
				mUpdatingActors = true;
				int x, y;
				SDL_GetMouseState(&x, &y);
				for (auto actor : mActors)
				{
					actor->ProcessInput(x, y);
				}
				mUpdatingActors = false;
				break;
		}
	}

	const Uint8* keyState = SDL_GetKeyboardState(NULL);
	if (keyState[SDL_SCANCODE_ESCAPE])
	{
		mIsRunning = false;
	}

}

void Game::UpdateGame()
{
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));

	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f; 
	mTicksCount = SDL_GetTicks();

	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}
	
	if (mState == GAMEOVER)
	{
		mIsRunning = false;
	}

	mUpdatingActors = true;
	for (auto actor : mActors)
	{
		actor->Update(deltaTime);
	}

	mUpdatingActors = false;

	for (auto pending : mPendingActors)
	{
	mActors.emplace_back(pending);
	}
	mPendingActors.clear();

	std::vector<Actor*> deadActors;
	for (auto actor : mActors)
	{
		if (actor->GetState() == Actor::EDead)
		{
			deadActors.emplace_back(actor);
		}
	}

	for (auto actor : deadActors)
	{
		delete actor;
	}

	if (!IsPlacingFinished())
	{
		std::ostringstream oss;
		std::string txt;
		if (mPlayerTurn == 1)
		{
			oss << "Pieces left : " << 9 - mPlayer1->GetCurrentlyPlacedPieces();
			txt = oss.str();
		}
		else if (mPlayerTurn == 2)
		{
			oss << "Pieces left : " << 9 - mPlayer2->GetCurrentlyPlacedPieces();
			txt = oss.str();
		}
		mTextPieces->SetTextTexture(GetTextTexture(txt));
	}

	DrawAvailablePositions();
	
}

void Game::DrawAvailablePositions()
{
	if (mPlayerTurn == 1 && mState == MOVING)
	{
		if (!mPlayer1->GetMovePieceFrom().empty())
		{
			std::vector<std::string> availablePositions = mBoard.GetNeighbours(mPlayer1->GetMovePieceFrom());
			for (int i = 0; i < availablePositions.size(); ++i)
			{
				if (mBoard.GetStateAtPosition(availablePositions[i]) == 0)
				{
					Actor* temp = new Actor(this);
					temp->SetPosition(mBoard.GetCoordinatesAt(availablePositions[i]));
					PieceSpriteComponent* piece = new PieceSpriteComponent(temp, 3, 70);
					piece->SetPieceSize(10);
					mAvailablePositions.push_back(piece);
				}
			}
		}
		else
		{
			if (!mAvailablePositions.empty())
			{
				for (int i = mAvailablePositions.size() - 1; i >= 0; i--)
				{
					delete(mAvailablePositions[i]);
					mAvailablePositions.pop_back();
				}
			}
		}
	}
	else if (mPlayerTurn == 2 && mState == MOVING)
	{
		if (!mPlayer2->GetMovePieceFrom().empty())
		{
			std::vector<std::string> availablePositions = mBoard.GetNeighbours(mPlayer2->GetMovePieceFrom());
			for (int i = 0; i < availablePositions.size(); ++i)
			{
				if (mBoard.GetStateAtPosition(availablePositions[i]) == 0)
				{
					Actor* temp = new Actor(this);
					temp->SetPosition(mBoard.GetCoordinatesAt(availablePositions[i]));
					PieceSpriteComponent* piece = new PieceSpriteComponent(temp, 3, 70);
					piece->SetPieceSize(10);
					mAvailablePositions.push_back(piece);
				}
			}
		}
		else
		{
			if (!mAvailablePositions.empty())
			{
				for (int i = mAvailablePositions.size() - 1; i >= 0; i--)
				{
					delete(mAvailablePositions[i]);
					mAvailablePositions.pop_back();
				}
			}
		}
	}
	else
	{
		if (!mAvailablePositions.empty())
		{
			for (int i = mAvailablePositions.size() - 1; i >= 0; i--)
			{
				delete(mAvailablePositions[i]);
				mAvailablePositions.pop_back();
			}
		}
	}
}

void Game::GenerateOutput()
{

	SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
	SDL_RenderClear(mRenderer);

	for (auto sprite : mSprites)
	{
		sprite->Draw(mRenderer);
	}

	SDL_RenderPresent(mRenderer);
}

void Game::AddActor(Actor* actor)
{
	if (mUpdatingActors)
	{
		mPendingActors.emplace_back(actor);
	}
	else
	{
		mActors.emplace_back(actor);
	}
}

void Game::RemoveActor(Actor* actor)
{
	auto iter = std::find(mPendingActors.begin(), mPendingActors.end(), actor);
	if (iter != mPendingActors.end())
	{
		std::iter_swap(iter, mPendingActors.end() - 1);
		mPendingActors.pop_back();
	}

	iter = std::find(mActors.begin(), mActors.end(), actor);
	if (iter != mActors.end())
	{
		std::iter_swap(iter, mActors.end() - 1);
		mActors.pop_back();
	}
}

void Game::AddSprite(SpriteComponent* sprite)
{
	int myDrawOrder = sprite->GetDrawOrder();
	auto iter = mSprites.begin();
	for (; iter != mSprites.end(); ++iter)
	{
		if (myDrawOrder < (*iter)->GetDrawOrder())
		{
			break;
		}
	}

	mSprites.insert(iter, sprite);
}

void Game::RemoveSprite(SpriteComponent *sprite)
{
	auto iter = std::find(mSprites.begin(), mSprites.end(), sprite);
	mSprites.erase(iter);
}

void Game::LoadData()
{
	Actor* temp = new Actor(this);
	temp->SetPosition(Vector2(512.0f, 384.0f));
	BGSpriteComponent* bg = new BGSpriteComponent(temp);
	bg->SetScreenSize(Vector2(1024.0f, 768.0f));
	std::vector<SDL_Texture*> bgtexs = {
		GetTexture("Assets/WoodTexture.png")
	};
	bg->SetBGTexture(bgtexs);

	bg = new BGSpriteComponent(temp, 50);
	bg->SetScreenSize(Vector2(500.0f, 500.0f));
	bgtexs = {
		GetTexture("Assets/Board.jpg")
	};
	bg->SetBGTexture(bgtexs);

	Actor* textPlayer = new Actor(this);
	textPlayer->SetPosition(Vector2(512.0f, 20.0f));
	mTextPlayer = new TextSpriteComponent(textPlayer);
	mTextPlayer->SetScreenSize(Vector2(250.0f, 80.0f));

	Actor* textDescription = new Actor(this);
	textDescription->SetPosition(Vector2(512.0f,630.0f));
	mTextDescription = new TextSpriteComponent(textDescription);
	mTextDescription->SetScreenSize(Vector2(600.0f, 60.0f));

	Actor* textPiece = new Actor(this);
	textPiece->SetPosition(Vector2(512.0f, 700.0f));
	mTextPieces = new TextSpriteComponent(textPiece);
	mTextPieces->SetScreenSize(Vector2(150.0f, 40.0f));


	mTextPlayer->SetTextTexture(GetTextTexture("Player 1 turn"));
	mTextDescription->SetTextTexture(GetTextTexture("Click an empty spot to place your piece"));
	mTextPieces->SetTextTexture(GetTextTexture("Pieces left: 9"));

	mBoard.InitializePositions();
	mBoard.ClearBoard();


	mPlayer1 = new Player(this, mBoard, 1);
	mPlayer2 = new Player(this, mBoard, 2);



}

void Game::UnloadData()
{
	while (!mActors.empty())
	{
		delete mActors.back();
	}

	for (auto i : mTextures)
	{
		SDL_DestroyTexture(i.second);
	}

	mTextures.clear();
	mTextDescription->Free();
}

SDL_Texture* Game::GetTexture(const std::string &fileName)
{
	SDL_Texture* tex = nullptr;
	auto iter = mTextures.find(fileName);
	if (iter != mTextures.end())
	{
		tex = iter->second;
	}
	else
	{
		SDL_Surface* surf = IMG_Load(fileName.c_str());
		if (!surf)
		{
			SDL_Log("Failed to load texture file: %s", fileName.c_str());
			return nullptr;
		}

		tex = SDL_CreateTextureFromSurface(mRenderer, surf);
		SDL_FreeSurface(surf);
		if (!tex)
		{
			SDL_Log("Failed to convert surface to texture for %s", fileName.c_str());
			return nullptr;
		}

		mTextures.emplace(fileName.c_str(), tex);
	}
	return tex;
}


SDL_Texture* Game::GetTextTexture(const std::string text)
{
	SDL_Texture* mTexture = nullptr;
	TTF_Font *gFont = TTF_OpenFont("ASMAN.ttf", 100);
	SDL_Color textColor = {11, 110, 79 };

	SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, text.c_str(), textColor);
	if (textSurface == NULL)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		mTexture = SDL_CreateTextureFromSurface(mRenderer, textSurface);
		if (mTexture == NULL)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		SDL_FreeSurface(textSurface);
		mTextures.emplace(text, mTexture);
	}
	return mTexture;
}

void Game::EndTurn() 
{
	mPlayerTurn = 3 - mPlayerTurn;

	if (mPlayerTurn == 1)
	{
		mTextPlayer->SetTextTexture(GetTextTexture("Player 1 turn"));
	}
	else if (mPlayerTurn == 2)
	{
		mTextPlayer->SetTextTexture(GetTextTexture("Player 2 turn"));
	}
}

void Game::NotifyPlacingFinished()
{
	mPlacingFinished++;
}

bool Game::IsPlacingFinished()
{
	if (mPlacingFinished >= 2)
	{
		return true;
	}
	return false;
}

void Game::SetGameState(GameState state) 
{
	mState = state;

	if (mState == PLACING)
	{
		mTextDescription->SetTextTexture(GetTextTexture("Click an empty spot to place your piece"));
	}
	if (mState == EATING)
	{
		mTextDescription->SetTextTexture(GetTextTexture("Mill! Click an opponent's piece to remove it"));
	}
	if (mState == MOVING)
	{
		mTextPieces->Free();
		mTextDescription->SetTextTexture(GetTextTexture("Click and select one of your pieces to move"));
	}
	if (mState == GAMEOVER)
	{
		if (mPlayerTurn == 1)
		{
			mTextDescription->SetTextTexture(GetTextTexture("Game Over! Player 1 Won!"));
		}
		else if (mPlayerTurn == 2)
		{
			mTextDescription->SetTextTexture(GetTextTexture("Game Over! Player 2 Won!"));
		}
	}

}