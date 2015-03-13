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
	SoundHandler *soundHandler = new SoundHandler(Camera::getInstance()->musResPath);

	//Music Loading
	soundHandler->loadSound("05 Intruder 1.mp3", "MUSIC");
	soundHandler->playSound("05 Intruder 1.mp3", "MUSIC");

	//Image Loading
	const std::string resPath = Camera::getInstance()->resPath;
	SDL_Renderer *renderer = Camera::getInstance()->renderer;

	SDL_Texture *marinezSS = loadTexture(resPath + "marinez 64px.png", renderer);
	SDL_Texture *marinezSSF = loadTexture(resPath + "marinez 64px flip.png", renderer);
	SDL_Texture *zealotSS = loadTexture(resPath + "zealot.png", renderer);
	SDL_Texture *zealotSSF = loadTexture(resPath + "zealot flip.png", renderer);
	SDL_Texture *zerglingSS = loadTexture(resPath + "zergling.png", renderer);
	SDL_Texture *zerglingSSF = loadTexture(resPath + "zergling flip.png", renderer);
	SDL_Texture *backgroundSS = loadTexture(resPath + "background2.png", renderer);

	Sprite *mainChar = new Sprite(64, 64, renderer);
	Sprite *zealot = new Sprite(38, 40, renderer);
	Sprite *zergling = new Sprite(39, 38, renderer);
	Sprite* spriteBG = new Sprite(Camera::getInstance()->SCREEN_WIDTH, Camera::getInstance()->SCREEN_HEIGHT, renderer);
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
	////MARINEZ FLIPPED
	for (int i = 0; i < 13; i++)
	{
		mainChar->addFrameToSequence("downLeft", mainChar->makeFrame(marinezSSF, 256, 64 * i));
	}
	for (int i = 0; i < 13; i++)
	{
		mainChar->addFrameToSequence("left", mainChar->makeFrame(marinezSSF, 512, 64 * i));
	}
	for (int i = 0; i < 13; i++)
	{
		mainChar->addFrameToSequence("upLeft", mainChar->makeFrame(marinezSSF, 768, 64 * i));
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
	///ZEALOT FLIP
	for (int i = 0; i < 8; i++)
	{
		zealot->addFrameToSequence("downLeft", zealot->makeFrame(zealotSSF, 85, 2 + (44 * i)));
	}
	for (int i = 0; i < 8; i++)
	{
		zealot->addFrameToSequence("left", zealot->makeFrame(zealotSSF, 169, 2 + (44 * i)));
	}
	for (int i = 0; i < 8; i++)
	{
		zealot->addFrameToSequence("upLeft", zealot->makeFrame(zealotSSF, 253, 2 + (44 * i)));
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
	///ZERGLING FLIP
	for (int i = 0; i < 8; i++)
	{
		zergling->addFrameToSequence("downLeft", zergling->makeFrame(zerglingSSF, 88, 2 + (42 * i)));
	}
	for (int i = 0; i < 8; i++)
	{
		zergling->addFrameToSequence("left", zergling->makeFrame(zerglingSSF, 174, 2 + (42 * i)));
	}
	for (int i = 0; i < 8; i++)
	{
		zergling->addFrameToSequence("upLeft", zergling->makeFrame(zerglingSSF, 260, 2 + (42 * i)));
	}

	int x = Camera::getInstance()->SCREEN_WIDTH / 2;
	int y = Camera::getInstance()->SCREEN_HEIGHT / 2;
	mainChar->setPos(x, y + -50);
	zergling->setPos(x + 50, y);
	zealot->setPos(x - 50, y + 50);

	
	// --------- ACTOR HANDLER --------- //



	std::string playerDirection = "up";
	std::string spriteDirection = "up";

	Camera::getInstance()->addRenderer(&mainChar->show(spriteDirection.c_str()));
	DisplayRenderer zealots = zealot->show(spriteDirection.c_str());

	SDL_Event e;
	bool quit = false;
	while (!quit){
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}

			else if (e.type == SDL_MOUSEMOTION)
			{
				Camera::getInstance()->graduallyMoveScreenTo(e.motion.xrel, e.motion.yrel);
			}

			else{
					engine.distributeSDLEvent(e);
			}

		}

		engine.update();
		

		//SDL_RenderClear(renderer);
		//spriteBG->show(bgFrame);

		//Camera::getInstance()->addRenderer( &spriteBG->show(bgFrame) );

		//Camera::getInstance()->addRenderer(&mainChar->show(spriteDirection.c_str()));
		//zergling->show(spriteDirection.c_str());
		//zealot->show(spriteDirection.c_str());
		//SDL_RenderPresent(renderer);

		engine.draw();
	}
	
	engine.events.terminateThread();
	soundHandler->freeMusic();
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
	return 0;
}