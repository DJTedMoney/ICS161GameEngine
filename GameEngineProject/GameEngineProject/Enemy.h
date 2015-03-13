#pragma once

#include "Character.h"

class Enemy : public Character{
public:

	//zerglings will have 1 attack, 1 health
	//Zealot will have 2 attack, 4 health
	Enemy(Sprite* sprite, int x, int y, std::string name, int h, int att_amt) :Character( sprite,  x,  y, name,  h,  att_amt){}

	findActor(Actor* actor, void (*func)()); // use AI to move to any actor's position
	void Attack();
};