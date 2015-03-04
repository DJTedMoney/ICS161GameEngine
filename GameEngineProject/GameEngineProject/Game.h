#pragma once
#include "Actor.h"
#include "Camera.h"
#include "GameEvent.h"
#include "SaveHandler.h"
#include "SoundHandler.h"

class Game
{
public:

	Game();
	~Game();

	void update();
	void draw();

	//GameEvent events;
	bool gameIsRunning;
	
private:

};