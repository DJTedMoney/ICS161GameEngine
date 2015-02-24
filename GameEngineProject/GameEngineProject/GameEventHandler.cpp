#include "GameEventHandler.h"

GameEventHandler::GameEventHandler(){
	
}


GameEventHandler::~GameEventHandler(){

}

void GameEventHandler::PushEvent(GameEvent e){
	gameEventQueue.push(e);
}

GameEvent GameEventHandler::GetNextEvent(){
	if (gameEventQueue.empty()){
		return GameEvent("none");
	}

	else
	{
		GameEvent e = gameEventQueue.front();
		gameEventQueue.pop();
		return e;
	}
}