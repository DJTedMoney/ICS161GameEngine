#include "Game.h"

Game::Game()
{
	//soundPlayer = new SoundHandler(mainCamera.musResPath);
	//soundPlayer->loadSound("05 Intruder 1", "MUSIC");
	gameIsRunning = true;
	isPaused = false;
	SDL_SetRelativeMouseMode(SDL_TRUE);
	SaveHandler::getInstance()->init();
	events.init();

	Camera::getInstance()->init(900, 600, "GameEngineProject");
	Camera::getInstance()->setBackground("background2.png");
}

void Game::distributeSDLEvent(SDL_Event toDistribute)
{
	if (toDistribute.key.keysym.sym == SDLK_p)
	{
		if (isPaused)
			isPaused = false;
		else
			isPaused = true;
	}
	
	if (!isPaused)
	{
		Camera::getInstance()->listenForEvent(toDistribute);
		soundPlayer->listenForEvent(toDistribute);
		//call player->PlayerInput(toDistribute); here
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
		Camera::getInstance()->update();
	}
}

void Game::draw()
{
	if (!isPaused)
		Camera::getInstance()->draw();
}

