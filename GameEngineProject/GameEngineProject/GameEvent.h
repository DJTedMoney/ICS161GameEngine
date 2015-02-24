#pragma once
#include <string>
#include <SDL_timer.h>





class GameEvent{

public:
	GameEvent(std::string type);
	~GameEvent();


private:
	//time
	Uint32 timestamp;


	//event type
	//it's currently a string, but we will probably end up changing it to something like an enum or an object or something
	std::string eventType;
};