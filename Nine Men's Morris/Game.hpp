#pragma once

#include<SDL.h>
#include<unordered_map>
#include<string>
#include<vector>
#include"Board.hpp"
#include"TextSpriteComponent.hpp"
#include"PieceSpriteComponent.hpp"
class Game
{
public:
	Game();
	bool Initialize();
	void RunLoop();
	void Shutdown(); 

	void Restart();

	void AddActor(class Actor* actor);
	void RemoveActor(class Actor* actor);

	void AddSprite(class SpriteComponent *sprite);
	void RemoveSprite(class SpriteComponent *sprite);

	SDL_Texture* GetTexture(const std::string &fileName);
	SDL_Texture* GetTextTexture(const std::string text);

	int GetPlayerTurn() { return mPlayerTurn; }
	void EndTurn();
	int GetPlayerWon() { return mPlayerWon; }
	void SetPlayerWon(int playerWon) { mPlayerWon = playerWon; }

	enum GameState { PLACING, EATING, MOVING, GAMEOVER };
	GameState GetGameState() { return mState; }
	void SetGameState(GameState state);

	void NotifyPlacingFinished();
	bool IsPlacingFinished();

private:
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	void LoadData();
	void UnloadData();
	void DrawAvailablePositions();

	std::unordered_map<std::string, SDL_Texture*> mTextures;

	std::vector<Actor*> mActors; 
	std::vector<Actor*> mPendingActors;

	std::vector<SpriteComponent*> mSprites;

	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	TextSpriteComponent* mTextPlayer;
	TextSpriteComponent* mTextDescription;
	TextSpriteComponent* mTextPieces;

	std::vector<PieceSpriteComponent*> mAvailablePositions;

	Uint32 mTicksCount;
	bool mIsRunning;
	bool mUpdatingActors;

	class Board mBoard;
	class Player* mPlayer1; 
	class Player* mPlayer2;

	int mPlayerTurn;
	int mPlayerWon;
	GameState mState;
	int mPlacingFinished;
};
