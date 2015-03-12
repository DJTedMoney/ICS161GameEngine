#pragma once 
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "SoundHandler.h"
#include "Game.h"
#include "Sprite.h"
//# include "Game.h"

SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren){
	SDL_Texture *texture = IMG_LoadTexture(ren, file.c_str());
	if (texture == nullptr){
		std::cout << "loadTexture" << std::endl;
	}
	return texture;
}


int main(int, char**)
{

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		std::cout << "Mix_OpenAudio Error" << std::endl;
		return 1;
	}

	if (Mix_Init(MIX_INIT_MP3) != MIX_INIT_MP3)
	{
		std::cout << "Mix_Init Error" << SDL_GetError() << std::endl;
		return 1;
	}


	//SDL_SETRELATIVEMOUSEMODE
	Game engine = Game();
	SoundHandler *soundHandler = new SoundHandler(engine.mainCamera.musResPath);

	//Music Loading
	//soundHandler->loadSound("05 Intruder 1.mp3", "MUSIC");

	//Image Loading
	const std::string resPath = engine.mainCamera.resPath;
	SDL_Renderer *renderer = engine.mainCamera.renderer;

	SDL_Texture *marinezSS = loadTexture(resPath + "marinez 64px.png", renderer);
	SDL_Texture *zealotSS = loadTexture(resPath + "zealot.png", renderer);
	SDL_Texture *zerglingSS = loadTexture(resPath + "zergling.png", renderer);
	SDL_Texture *backgroundSS = loadTexture(resPath + "background.png", renderer);

	Sprite *mainChar = new Sprite(64, 64, renderer);
	Sprite *zealot = new Sprite(38, 40, renderer);
	Sprite *zergling = new Sprite(39, 38, renderer);
	Sprite* spriteBG = new Sprite(engine.mainCamera.SCREEN_WIDTH, engine.mainCamera.SCREEN_HEIGHT, renderer);
	spriteBG->setPos(0, 0);
	int bgFrame = spriteBG->makeFrame(backgroundSS, 0, 0);

	///MARINEZ
	for (int i = 0; i < 13; i++)
	{
		mainChar->addFrameToSequence("up", mainChar->makeFrame(marinezSS, 0, 64 * i));
	}
	for (int i = 0; i < 13; i++)
	{
		mainChar->addFrameToSequence("upRight", mainChar->makeFrame(marinezSS, 256, 64 * i));
	}
	for (int i = 0; i < 13; i++)
	{
		mainChar->addFrameToSequence("right", mainChar->makeFrame(marinezSS, 512, 64 * i));
	}
	for (int i = 0; i < 13; i++)
	{
		mainChar->addFrameToSequence("downRight", mainChar->makeFrame(marinezSS, 768, 64 * i));
	}
	for (int i = 0; i < 13; i++)
	{
		mainChar->addFrameToSequence("down", mainChar->makeFrame(marinezSS, 1024, 64 * i));
	}

	///ZEALOT
	for (int i = 0; i < 8; i++)
	{
		zealot->addFrameToSequence("up", zealot->makeFrame(zealotSS, 1, 2 + (44 * i)));
	}
	for (int i = 0; i < 8; i++)
	{
		zealot->addFrameToSequence("upRight", zealot->makeFrame(zealotSS, 85, 2 + (44 * i)));
	}
	for (int i = 0; i < 8; i++)
	{
		zealot->addFrameToSequence("right", zealot->makeFrame(zealotSS, 169, 2 + (44 * i)));
	}
	for (int i = 0; i < 8; i++)
	{
		zealot->addFrameToSequence("downRight", zealot->makeFrame(zealotSS, 253, 2 + (44 * i)));
	}
	for (int i = 0; i < 8; i++)
	{
		zealot->addFrameToSequence("down", zealot->makeFrame(zealotSS, 337, 2 + (44 * i)));
	}

	///ZERGLING
	for (int i = 0; i < 8; i++)
	{
		zergling->addFrameToSequence("up", zergling->makeFrame(zerglingSS, 2, 2 + (42 * i)));
	}
	for (int i = 0; i < 8; i++)
	{
		zergling->addFrameToSequence("upRight", zergling->makeFrame(zerglingSS, 88, 2 + (42 * i)));
	}
	for (int i = 0; i < 8; i++)
	{
		zergling->addFrameToSequence("right", zergling->makeFrame(zerglingSS, 174, 2 + (42 * i)));
	}
	for (int i = 0; i < 8; i++)
	{
		zergling->addFrameToSequence("downRight", zergling->makeFrame(zerglingSS, 260, 2 + (42 * i)));
	}
	for (int i = 0; i < 8; i++)
	{
		zergling->addFrameToSequence("down", zergling->makeFrame(zerglingSS, 346, 2 + (42 * i)));
	}

	int x = engine.mainCamera.SCREEN_WIDTH / 2;
	int y = engine.mainCamera.SCREEN_HEIGHT / 2;
	mainChar->setPos(x, y + -50);
	zergling->setPos(x + 50, y);
	zealot->setPos(x - 50, y + 50);

	std::string spriteDirection = "up";
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
		SDL_SetRelativeMouseMode(SDL_TRUE);
		auto r = SDL_GetMouseState(&xChange, &yChange);
		std::cout << "Relative move x/y: " << xChange << "," << yChange << std::endl;


		if (xChange != 0 || yChange != 0)
			engine.mainCamera.graduallyMoveScreenTo(xChange, yChange);

		engine.update();
		engine.draw();

		//SDL_RenderClear(renderer);
		//spriteBG->show(bgFrame);
		//mainChar->show(spriteDirection.c_str());
		//zergling->show(spriteDirection.c_str());
		//zealot->show(spriteDirection.c_str());
		//SDL_RenderPresent(renderer);

	}
	
	engine.events.terminateThread();
	soundHandler->freeMusic();
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
	return 0;
}