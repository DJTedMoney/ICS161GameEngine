#include "GameEventHandler.h"

GameEventHandler::GameEventHandler(){}


GameEventHandler::~GameEventHandler(){}

void GameEventHandler::PushEvent(GameEvent e){
	gameEventQueue.push(e);
}

void GameEventHandler::Update(){
	Pop_Event();
}

int GameEventHandler::GetNextEvent(GameEvent &ge){
	if (gameEventQueue.empty()){
		return 0;
	}

	else
	{
		ge = gameEventQueue.front();
		return 1;
	}
}

void GameEventHandler::Pop_Event(){
	if (!gameEventQueue.empty()){
		gameEventQueue.pop();
	}
}