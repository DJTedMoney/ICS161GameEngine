#include "Camera.h"

Camera::Camera()
{

}

Camera::~Camera()
{

}

void Camera::init(int width, int height)
{
	window = SDL_CreateWindow("GameEngineProject", 800, 100, SCREEN_WIDTH,
		SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	if (window == nullptr)
	{
		std::cout << "CreateWindow Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
	}

}

void Camera::update()
{
	//If some event calls for it change Camera position or other actions
}

void Camera::draw()
{
	//Render here
}