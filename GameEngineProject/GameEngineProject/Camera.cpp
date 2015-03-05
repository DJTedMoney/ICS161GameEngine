#include "Camera.h"
#include "res_path.h"
#include "cleanup.h"

Camera::Camera()
{

}

Camera::~Camera()
{
	cleanup(background, renderer, window);
}

bool Camera::init(int width, int height)
{
	resPath = getResourcePath("Images");
	window = SDL_CreateWindow("GameEngineProject", 800, 100, SCREEN_WIDTH,
		SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == nullptr)
	{
		std::cout << "CreateWindow Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
	}

	renderer = SDL_CreateRenderer(window, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr)
	{
		std::cout << "Renderer Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

}

bool Camera::setBackground(std::string imageName)
{
	const std::string resPath = getResourcePath("Images") + "background.png";

	background = IMG_LoadTexture(renderer, resPath.c_str());

	if (background == nullptr)
	{
		std::cout << "LoadTexture Error: " << SDL_GetError() << std::endl;
		return false;
	}
	else
		return true;



}

void Camera::update()
{
	//If some event calls for it change Camera position or other actions
}

void Camera::draw()
{
	//Render here
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, background, NULL, NULL);
	SDL_RenderPresent(renderer);
}