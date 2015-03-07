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
	SCREEN_HEIGHT = height;
	SCREEN_WIDTH = width;
	displayArea = { 0, 0, width, height };

	resPath = getResourcePath("Images");
	window = SDL_CreateWindow("GameEngineProject", 800, 100, width,
		height, SDL_WINDOW_SHOWN);
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

void Camera::graduallyMoveScreenTo(int x, int y)
{
	moveToX = x;
	moveToY = y;
	movingScreen = true;
}

void Camera::moveCameraToPosition()
{
	if (currX != moveToX)
	{
		currX += 2;
	}
	if (currY != moveToY)
	{

	}
}

void Camera::update()
{
	//If some event calls for it change Camera position or other actions
}

void Camera::draw()
{
	//Render here
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, background, NULL, &displayArea);
	SDL_RenderPresent(renderer);
}