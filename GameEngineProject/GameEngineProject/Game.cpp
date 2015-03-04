#include "Game.h"

Game::Game()
{
	gameIsRunning = true;
	SaveHandler::getInstance()->init();
	events.init();
}

Game::~Game()
{

}

void Game::draw()
{

}

void Game::update()
{
	
}