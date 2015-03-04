#pragma once
#include <SDL_image.h>
#include <iostream>
class Camera
{
public: 

	Camera();
	~Camera();

	void update();
	void draw();
	//add parameters to allow for diffrent screen sizes ect
	void init(int width, int height);

	SDL_Window* window;

	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;

private:

};