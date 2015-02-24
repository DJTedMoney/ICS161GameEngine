#pragma once
#include <string>
#include <queue>
#include "GameEvent.h"

class GameEventHandler
{

public:
	//Might need to have a string as a parameter to know where to look to load sounds
	GameEventHandler();
	~GameEventHandler();

	//Add event to the queue
	void PushEvent(GameEvent e);


	//listen for events


	//get next event
	GameEvent GetNextEvent();


private:

	std::queue<GameEvent>  gameEventQueue;

};