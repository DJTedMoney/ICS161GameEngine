#include "Game.h"

Game::Game()
{
	gameIsRunning = true;
	isPaused = false;
	SaveHandler::getInstance()->init();
	events.init();

	mainCamera.init(640, 480);
	mainCamera.setBackground("background.png");
}

void Game::distributeSDLEvent(SDL_Event toDistribute)
{
	//Call classes listenForSDLEvent that have one.
}

Game::~Game()
{

}

void Game::update()
{
	if (isPaused)
		return;
	else
	{
		//Call peoples updates.
		mainCamera.update();
	}
}

void Game::draw()
{
	mainCamera.draw();
}

