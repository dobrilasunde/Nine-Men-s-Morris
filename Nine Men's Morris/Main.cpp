#include"Game.hpp"
#include<iostream>
int main(int argc, char** argv)
{

	Game game;
	bool success = game.Initialize();

	if (success)
	{
		game.RunLoop();
	}
	game.Shutdown();

	return 0;
}