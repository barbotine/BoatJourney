#pragma once

enum GameState
{
	GAMEOVER,
	INGAME,
	WIN,
	PAUSE
};

class Game
{
	private :
		GameState currentState;

	public : 
		Game();
		void setCurrentState(GameState state);
		GameState getCurrentState();

};

