#pragma once
#include <SDL_image.h>
#include <iostream>
#include "SaveHandler.h"


class Camera
{
public: 

	Camera();
	~Camera();

	void update();
	void draw();
	//add parameters to allow for diffrent screen sizes ect
	bool init(int width, int height);
	bool setBackground(std::string myPath);

	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* background;

	std::string resPath;
	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;

private:

};