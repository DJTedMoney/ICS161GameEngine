#pragma once
#include "Actor.h"
#include "Camera.h"
#include "GameEvent.h"
#include "SaveHandler.h"
#include "SoundHandler.h"
#include "GameEventHandler.h"

class Game
{
public:

	Game();
	~Game();

	void update();
	void draw();
	void distributeSDLEvent(SDL_Event toDistribute);

	bool isPaused;
	GameEventHandler events;
	bool gameIsRunning;
	Camera mainCamera;
	SoundHandler soundPlayer;
	
private:

};