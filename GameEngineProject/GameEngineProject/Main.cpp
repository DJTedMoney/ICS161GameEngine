#pragma once 
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "SoundHandler.h"
#include "Game.h"
//# include "Game.h"
int main(int, char**)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}
	//SDL_SETRELATIVEMOUSEMODE
	Game engine =  Game();
	
	SDL_Event e;
	bool quit = false;
	while (!quit){
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
			if (e.type == SDL_KEYDOWN){
				if (e.key.keysym.sym == SDLK_RIGHT)
				{
					engine.mainCamera.moveCameraRight();
				} 
				else if (e.key.keysym.sym == SDLK_LEFT)
				{
					engine.mainCamera.moveCameraLeft();
				}
				else if (e.key.keysym.sym == SDLK_UP)
				{
					engine.mainCamera.moveCameraUp();
				}
				else if (e.key.keysym.sym == SDLK_DOWN)
				{
					engine.mainCamera.moveCameraDown();
				}
			}
		}
		//Render the scene
		int xChange = 0, yChange = 0;
		auto r = SDL_GetMouseState(&xChange, &yChange);
		std::cout << "Relative move x/y: " << xChange << "," << yChange << std::endl;


		if (xChange != 0 || yChange != 0)
			engine.mainCamera.graduallyMoveScreenTo(xChange, yChange);

		engine.update();
		engine.draw();
	}

	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
	return 0;
}