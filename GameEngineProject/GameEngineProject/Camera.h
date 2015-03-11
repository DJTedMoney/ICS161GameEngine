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

	//Takes an x and a y amount to move the screen.
	//Relative to the mouse movement
	void graduallyMoveScreenTo(int x, int y);
	void moveCameraRight();
	void moveCameraLeft();
	void moveCameraUp();
	void moveCameraDown();

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
	SDL_Rect movedCamera;
	bool movingScreen;
	int moveToX;
	int moveToY;
	int currX;
	int currY;
	bool xMoved;
	bool yMoved;
	bool xPositive;
	bool yPositive;
};