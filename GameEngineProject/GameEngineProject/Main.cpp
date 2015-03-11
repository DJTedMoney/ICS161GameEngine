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
					//Play sound effect
				} 
				else if (e.key.keysym.sym == SDLK_LEFT)
				{
					//Play background music
				
				}
				else if (e.key.keysym.sym == SDLK_UP)
				{
					//pause music
					
				}
				else if (e.key.keysym.sym == SDLK_DOWN)
				{
					//resume music		
				}
			}
		}
		//Render the scene
		engine.draw();
	}

	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
	return 0;
}