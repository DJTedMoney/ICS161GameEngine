#include "Camera.h"
#include "res_path.h"
#include "cleanup.h"

Camera* Camera::instance;

Camera* Camera::getInstance()
{
	if (!instance)
		instance = new Camera;
	return instance;
}


Camera::~Camera()
{
	cleanup(background, renderer, window);
}

void Camera::listenForEvent(SDL_Event e)
{
	if (e.key.keysym.sym == SDLK_m)
	{
		isPanning = !isPanning;
	}
	else if (e.key.keysym.sym == SDLK_RIGHT)
	{
		moveCameraRight();
	}
	else if (e.key.keysym.sym == SDLK_LEFT)
	{
		moveCameraLeft();
	}
	else if (e.key.keysym.sym == SDLK_UP)
	{
		moveCameraUp();
	}
	else if (e.key.keysym.sym == SDLK_DOWN)
	{
		moveCameraDown();
	}
	
}

bool Camera::init(int width, int height, std::string windowName)
{
	SCREEN_HEIGHT = height;
	SCREEN_WIDTH = width;
	currX = 0;
	currY = 0;
	movingScreen = false;
	displayArea = { 0, 0, width, height };
	isPanning = false;

	resPath = getResourcePath("Images");
	musResPath = getResourcePath("Music");

	window = SDL_CreateWindow(windowName.c_str(), 400, 100, width,
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
	const std::string resPath = getResourcePath("Images") + imageName;
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

	int picWidth = 0;
	int picHeight = 0;
	SDL_QueryTexture(background, NULL, NULL, &picWidth, &picHeight);

	if (displayArea.x + x < 0){displayArea.x = 0;}
	else if (displayArea.x + x > picWidth - SCREEN_WIDTH){ displayArea.x = picWidth - SCREEN_WIDTH; }
	else{displayArea.x += x;}
	
	if (displayArea.y + y < 0){ displayArea.y = 0; }
	else if (displayArea.y + y > picHeight - SCREEN_HEIGHT){ displayArea.y = picHeight - SCREEN_HEIGHT; }
	else { displayArea.y += y; }
}

void Camera::moveCameraToPosition()
{
	//If x/y aren't at the given position then update them
	currX += (moveToX - currX);
	currY += (moveToY - currY);

	if (currX < 0){ currX = 0; }
	if (currY < 0){ currY = 0; }


	movingScreen = false;
	//Make new display rect
	displayArea.x = currX + 10;
	displayArea.y = currY + 10;
}

void Camera::update()
{
	if (isPanning)
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

void Camera::addRenderer(DisplayRenderer* myRend)
{
	toRender.push_back(myRend);
}

void Camera::copyTexture(SDL_Texture* toAdd)
{
	SDL_RenderCopy(renderer, toAdd,NULL, &displayArea);
}

void Camera::copyToRenderer()
{
	DisplayRenderer* temp;
	for (auto& add: toRender)
	{
		temp = add;
		if (temp->texture != NULL)
			SDL_RenderCopy(renderer, add->texture, &add->src,&add->src);
	}
}

void Camera::setMousePanning(bool toSet)
{
	isPanning = toSet;
}

void Camera::toggleMode()
{
	isPanning = !isPanning;
}

void Camera::draw()
{
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, background, &displayArea, NULL);
	copyToRenderer();
	SDL_RenderPresent(renderer);
}

