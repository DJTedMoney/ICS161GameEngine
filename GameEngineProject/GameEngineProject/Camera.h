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

	//Takes an x and a y that it will gracefully move the camera to
	//Call only once. Camera takes care of the rest
	void graduallyMoveScreenTo(int x, int y);

	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* background;

	std::string resPath;
	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;

private:
	//Variables to move screen to given position
	void moveCameraToPosition();
	SDL_Rect displayArea;
	bool movingScreen;
	int moveToX;
	int moveToY;
	int currX;
	int currY;

};