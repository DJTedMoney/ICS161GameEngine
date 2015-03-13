#pragma once
#include <SDL_image.h>
#include <iostream>
#include "SaveHandler.h"
#include <vector>
#include "RenderStruct.h"
#include "Sprite.h"

class Camera
{
public: 

	~Camera();
	static Camera* getInstance();

	void update();
	void draw();
	//add parameters to allow for diffrent screen sizes ect
	bool init(int width, int height, std::string windowName);
	bool setBackground(std::string myPath);

	//Takes an x and a y amount to move the screen.
	//Relative to the mouse movement
	void graduallyMoveScreenTo(int x, int y);
	//Moves the camera a set amount in the given direction
	void moveCameraRight();
	void moveCameraLeft();
	void moveCameraUp();
	void moveCameraDown();
	void listenForEvent(SDL_Event e);
	//Toggles between panning and not
	void setMousePanning(bool isPanning);
	void toggleMode();
	void addRenderer(DisplayRenderer* myRender);
	void copyTexture(SDL_Texture* toAdd);

	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* background;

	std::string resPath;
	std::string musResPath;
	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;

private:

	std::vector<DisplayRenderer*> toRender;
	void copyToRenderer();

	static Camera* instance;

	Camera(const Camera&);
	Camera& operator=(const Camera&);
	Camera() {}

	//Variables to move screen to given position
	void moveCameraToPosition();
	bool isPanning;
	SDL_Rect displayArea;
	SDL_Rect movedCamera;
	bool movingScreen;
	int moveToX;
	int moveToY;
	int currX;
	int currY;
};