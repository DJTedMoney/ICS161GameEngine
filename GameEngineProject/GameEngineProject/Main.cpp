#pragma once
#include <iostream>
#include <cleanup.h>
#include <res_path.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "SoundHandler.h"
#include "SaveHandler.h"
#include "Camera.h"

int main(int, char**)
{
	Camera mainCamera;
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0){
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	//Initializes MP3 loading
	int mp3flag = MIX_INIT_MP3;
	int initted = Mix_Init(mp3flag);

	if (initted && mp3flag != mp3flag)
	{
		std::cout << "MP3 INITIALIZING ERROR" << SDL_GetError() << std::endl;
		return 1;
	}


	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG){
		std::cout << "IMG_Init Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	mainCamera.init(5500, 444);

	SDL_Renderer *renderer = SDL_CreateRenderer(mainCamera.window, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr){
		std::cout << "Renderer Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		std::cout << "Music Error: " << Mix_GetError() << std::endl;
		SDL_Quit();
		return 1;
		
	}

	const std::string resPath = getResourcePath("Images");
	SDL_Texture *background = SaveHandler::getInstance()->loadTexture(resPath + "background.png", renderer);
	if (background == nullptr){
		cleanup(background, renderer, mainCamera.window);
		IMG_Quit();
		SDL_Quit();
		return 1;
	}

	std::string musResPath = getResourcePath("Music");
	SoundHandler* soundHandler = new SoundHandler(musResPath);
	soundHandler->loadSound("scratch.wav", "SFX");
	soundHandler->loadSound("Sample.wav", "MUSIC");
	soundHandler->loadSound("G Slamdam.mp3", "MUSIC");


	SDL_Event e;
	bool quit = false;
	while (!quit){
		while (SDL_PollEvent(&e)){
			if (e.type == SDL_QUIT){
				quit = true;
			}
			if (e.type == SDL_KEYDOWN){
				if (e.key.keysym.sym == SDLK_RIGHT)
				{
					//Play sound effect
					soundHandler->playSound("scratch.wav", "SFX");
				}
				else if (e.key.keysym.sym == SDLK_LEFT)
				{
					//Play background music
					soundHandler->playSound("G Slamdam.mp3", "MUSIC");
				}
				else if (e.key.keysym.sym == SDLK_UP)
				{
					//pause music
					soundHandler->pauseSound();
				}
				else if (e.key.keysym.sym == SDLK_DOWN)
				{
					//resume music
					soundHandler->resumeSound();
				}
			}
		}
		//Render the scene
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, background, NULL, NULL);
		SDL_RenderPresent(renderer);
	}

	cleanup(background, renderer, mainCamera.window);
	soundHandler->freeMusic();
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
	return 0;
}