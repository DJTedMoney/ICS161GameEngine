#pragma once
#include "Actor.h"


enum CHARACTER_DIRECTION{
	UP_LEFT,

	UP,

	UP_RIGHT,

	LEFT,

	RIGHT,

	DOWN_LEFT,

	DOWN,

	DOWN_RIGHT
};

class Character : public Actor{
public:

	//will always be interactible
	Character(Sprite* sprite, int x, int y, std::string name, int h, int att_amt) :
		Actor(sprite, x, y, name, true) {
		health = h;
		attackAmount = att_amt;
		dir = CHARACTER_DIRECTION::UP;
	}


	void MoveCharacter(int x, int y){
		//up left
		if (x < 0 && y < 0){ 
			dir = CHARACTER_DIRECTION::UP_LEFT;
			movex(x);
			movey(y);
		}
		
		//up right
		else if (x > 0 && y < 0 ){ 
			dir = CHARACTER_DIRECTION::UP_RIGHT;
			movex(x);
			movey(y);
		}

		//up
		else if (x == 0 & y < 0){ 
			dir = CHARACTER_DIRECTION::UP; 
			movey(y);
		}
		
		//down left
		else if (x < 0  && y > 0){
			dir = CHARACTER_DIRECTION::DOWN_LEFT;
			movex(x);
			movey(y);
		}

		
		//down right
		else if (x > 0 && y > 0){
			dir = CHARACTER_DIRECTION::DOWN_RIGHT;
			movex(x);
			movey(y);
		}

		
		//down
		else if (x == 0 && y > 0){ 
			dir = CHARACTER_DIRECTION::DOWN;
			movey(y);
		}
		
		//left
		else if (x < 0 && y == 0){
			dir = CHARACTER_DIRECTION::LEFT;
			movex(x);
		}
		
		//right
		else if (x > 0 && y == 0){ 
			dir = CHARACTER_DIRECTION::RIGHT;
			movex(x);
		}
	}

	void executeAI( void (*func)() );

	int health;
	int attackAmount;
	CHARACTER_DIRECTION dir;


};