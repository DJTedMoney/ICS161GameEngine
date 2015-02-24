#include "GameEvent.h"

GameEvent::GameEvent(std::string type){
	timestamp = SDL_GetTicks();
	eventType = type;
}

GameEvent::~GameEvent(){

}