#include "GameEventHandler.h"

GameEventHandler::GameEventHandler(){}


GameEventHandler::~GameEventHandler(){}

void GameEventHandler::PushEvent(GameEvent e){
	gameEventQueue.push(e);
}

void GameEventHandler::init()
{
	//Starts a thread with update as it's function call. 
	//If you want another function to be called just change the update
	eventThread = std::thread(&GameEventHandler::Update , this);
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