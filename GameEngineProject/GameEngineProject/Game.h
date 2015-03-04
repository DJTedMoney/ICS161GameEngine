#pragma once
#include "Actor.h"
#include "Camara.h"
#include "GameEvent.h"
#include "SaveHandler.h"
#include "SoundHandler.h"

class Game
{
public:

	Game();
	~Game();

	void init();
	void update();
	void draw();

	bool gameIsRunning;
	
private:

};