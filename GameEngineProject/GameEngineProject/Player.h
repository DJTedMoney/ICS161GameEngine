#pragma once

#include "Character.h"

class Player : public Character{
public:
	//sprite is the marine
	//player has 2 attack and 5 health
	Player(Sprite *s, int x, int y) : Character(s, x, y, "Player", 5, 2){ up = false; right = false; down = false; left = false; }
	void PlayerInput(SDL_Event &e);
	void AttackEnemy();

private:
	bool up;
	bool right;
	bool left;
	bool down;
};