#pragma once
#include <string>
#include <queue>

class EventHandler
{

public:
	//Might need to have a string as a parameter to know where to look to load sounds
	EventHandler();
	~EventHandler();

	void listenForEvents();

private:
	
	//Replace string with something better. 
	std::queue<std::string>  eventQueue;

};