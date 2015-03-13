#include "Game.h"

Game::Game()
{
	gameIsRunning = true;
	isPaused = false;
	SDL_SetRelativeMouseMode(SDL_TRUE);
	SaveHandler::getInstance()->init();
	events.init();

	mainCamera.init(900, 600);
	mainCamera.setBackground("background.png");
}

void Game::distributeSDLEvent(SDL_Event toDistribute)
{
	//Call classes listenForSDLEvent that have one.
	mainCamera.listenForEvent(toDistribute);
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
		mainCamera.update();
	}
}

void Game::draw()
{
	mainCamera.draw();
}

