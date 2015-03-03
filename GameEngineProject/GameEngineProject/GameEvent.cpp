#include "GameEvent.h"

GameEvent::GameEvent(EVENT_TYPE type, std::string src, void* ed){
	timestamp = SDL_GetTicks();
	eventType = type;
	source = src;
	extraData = ed;
}

GameEvent::~GameEvent(){
	delete extraData;
	extraData = nullptr;
}