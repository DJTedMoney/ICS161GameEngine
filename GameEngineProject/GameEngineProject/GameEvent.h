#pragma once
#include <string>
#include <SDL_timer.h>

enum EVENT_TYPE{

	//0
	NONE,

	//1
	HERO_CREATED,

	//2
	HERO_ATTACKS,

	//3
	HERO_INJURED,

	//4
	HERO_DIED,

	//5
	ENEMY_CREATED,

	//6
	ENEMY_ATTACKS,

	//7
	ENEMY_INJURED,

	//8
	ENEMY_DIED,

	//9
	COLLIDED,

	//10
	PAUSE

	//11
};

class GameEvent{

public:
	GameEvent(EVENT_TYPE type, std::string src, void* ed);
	~GameEvent();


private:
	//time
	Uint32 timestamp;

	//event type
	EVENT_TYPE eventType;

	std::string source;

	void* extraData;
};