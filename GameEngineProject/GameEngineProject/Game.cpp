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
	if (toDistribute.key.keysym.sym == SDLK_t)
	{
		if (isPaused)
			isPaused = false;
		else
			isPaused = true;
	}
	
	if (!isPaused)
	{
		mainCamera.listenForEvent(toDistribute);
	}
		
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
	if (!isPaused)
		mainCamera.draw();
}

