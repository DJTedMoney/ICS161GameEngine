#include "Camara.h"

Camara::Camara()
{

}

Camara::~Camara()
{

}

void Camara::init(int width, int height)
{
	window = SDL_CreateWindow("GameEngineProject", 800, 100, SCREEN_WIDTH,
		SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	if (window == nullptr)
	{
		std::cout << "CreateWindow Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
	}

}

void Camara::update()
{
	//If some event calls for it change camara position or other actions
}

void Camara::draw()
{
	//Render here
}