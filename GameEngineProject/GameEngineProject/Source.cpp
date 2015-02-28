#include <iostream>
#include <cleanup.h>
#include <res_path.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "SoundHandler.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren){
	SDL_Texture *texture = IMG_LoadTexture(ren, file.c_str());
	if (texture == nullptr){
		std::cout << "LoadTexture Error: " << SDL_GetError() << std::endl;
	}
	return texture;
}

int main(int, char**){
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0){
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG){
		std::cout << "IMG_Init Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	SDL_Window *window = SDL_CreateWindow("GameEngineProject", 800, 100, SCREEN_WIDTH,
		SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == nullptr){
		std::cout << "CreateWindow Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1,
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
	SDL_Texture *background = loadTexture(resPath + "background.png", renderer);
	if (background == nullptr){
		cleanup(background, renderer, window);
		IMG_Quit();
		SDL_Quit();
		return 1;
	}

	std::string musResPath = getResourcePath("Music");
	SoundHandler* soundHandler = new SoundHandler(musResPath);
	soundHandler->loadSound("scratch.wav", "SFX");


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
					soundHandler->playSound("scratch.wav");
				}
				else if (e.key.keysym.sym == SDLK_LEFT)
				{

				}
				else if (e.key.keysym.sym == SDLK_UP)
				{

				}
				else if (e.key.keysym.sym == SDLK_DOWN)
				{

				}
			}
		}
		//Render the scene
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, background, NULL, NULL);
		SDL_RenderPresent(renderer);
	}

	cleanup(background, renderer, window);
	soundHandler->freeMusic();
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
	return 0;
}