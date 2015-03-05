#include "Game.h"

Game::Game()
{
	gameIsRunning = true;
	SaveHandler::getInstance()->init();
	events.init();

	mainCamera.init(5500, 444);
	mainCamera.setBackground("background.png");

}

Game::~Game()
{

}

void Game::update()
{

}

void Game::draw()
{
	mainCamera.draw();
}

