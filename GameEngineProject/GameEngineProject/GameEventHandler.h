#pragma once
#include <string>
#include <queue>
#include "GameEvent.h"
#include "SDL_events.h"



//needs:
	//a way for game functions to be able to listen for events
	//a way to notify the game functions of an event that happened


class GameEventHandler
{

public:
	GameEventHandler();
	~GameEventHandler();

	//Add event to the queue
	void PushEvent(GameEvent e);


	//get next event
	int GetNextEvent(GameEvent &ge);


private:

	std::queue<GameEvent>  gameEventQueue;
	void Pop_Event();
};