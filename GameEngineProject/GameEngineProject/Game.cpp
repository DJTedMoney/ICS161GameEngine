#include "Game.h"

Game::Game()
{
	SaveHandler::getInstance()->init();
}

Game::~Game()
{

}

void Game::init()
{
	gameIsRunning = true;
}

void Game::draw()
{

}