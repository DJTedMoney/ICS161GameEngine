#pragma once
#include "Actor.h"

class Character : public Actor{
public:
	void executeAI( void (*func)() );

private:
	int health;
	int attack;

	//characters need health
	//and attack
	//and... other stuff?

};