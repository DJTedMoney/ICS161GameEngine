#pragma once

#include "Character.h"

class Enemy : public Character{
public:
	findActor(Actor* actor, void (*func)()); // use AI to move to any actor's position
};