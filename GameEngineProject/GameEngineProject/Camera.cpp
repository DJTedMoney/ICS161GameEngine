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
	currX = 0;
	currY = 0;
	movingScreen = false;
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
	//Check to see if either x/y are negative to move in the proper direction
	if (!movingScreen)
	{
		moveToX =  x - SCREEN_WIDTH/2;
		moveToY =  y - SCREEN_WIDTH/2;
		movingScreen = true;
	}
}

void Camera::moveCameraToPosition()
{
	//If x/y aren't at the given position then update them
	currX += (moveToX - currX) / 15;
	currY += (moveToY - currY) / 15;

	//Check to see if x and y have gone past their x/y
	

	movingScreen = false;
	//Make new display rect
	displayArea.x = currX;
	displayArea.y = currY;
}

void Camera::update()
{
	if (movingScreen)
		moveCameraToPosition();
	//If some event calls for it change Camera position or other actions
}

void Camera::moveCameraRight()
{
	displayArea.x += 5;
}

void Camera::moveCameraLeft()
{
	displayArea.x -= 5;
}

void Camera::moveCameraUp()
{
	displayArea.y -= 5;
}

void Camera::moveCameraDown()
{
	displayArea.y += 5;
}

void Camera::draw()
{
	//Render here
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, background, NULL, &displayArea);
	SDL_RenderPresent(renderer);
}