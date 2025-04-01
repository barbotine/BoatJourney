#include "Game.h"

Game::Game()
{
	this->currentState = GameState::INGAME;
}

void Game::setCurrentState(GameState state)
{
	this->currentState = state;
}

GameState Game::getCurrentState()
{
	return currentState;
}


