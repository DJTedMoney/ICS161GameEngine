#pragma once
#include <string>
#include <queue>
#include "GameEvent.h"
#include <thread> 
//#include "SDL_events.h"



//needs:
	//a way for game functions to be able to listen for events
	//a way to notify the game functions of an event that happened


//add an Update() function: pops off the head of the queue

class GameEventHandler
{

public:
	GameEventHandler();
	~GameEventHandler();

	//Add event to the queue
	void PushEvent(GameEvent e);


	//get next event
	int GetNextEvent(GameEvent &ge);
	void init();
	void Update();


private:

	std::thread eventThread;
	std::queue<GameEvent>  gameEventQueue;
	void Pop_Event();
};