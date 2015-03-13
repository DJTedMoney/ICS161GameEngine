#include "Player.h"

//need to add a check: for LR, if previous was U/D, then combine. And vice versa.
void Player::PlayerInput(SDL_Event &e){
	
	SDL_PollEvent(&e);



	//actually, this won't work at all.
	//need to rewrite it using flags.
	//at least that will make checking UL/UR easier.
	if (e.type == SDL_KEYDOWN){
		switch (e.key.keysym.sym){
		
		//left
		case SDLK_a:
			left = true;
			break;
		
		//right
		case SDLK_d:
			right = true;
			break;
		
		//up
		case SDLK_w:
			up = true;
			break;
		
		//down
		case SDLK_s:
			down = true;
			break;

		//attack
		case SDLK_SPACE:
			AttackEnemy();
			break;
		default:
			break;
		}
	}//end SDL_KEYDOWN

	else if (e.type == SDL_KEYUP){
		switch (e.key.keysym.sym){
			//left
		case SDLK_a:
			left = false;
			break;

			//right
		case SDLK_d:
			right = false;
			break;

			//up
		case SDLK_w:
			up = false;
			break;

			//down
		case SDLK_s:
			down = false;
			break;
		}
	}//end SDL_KEYUP

	if (up && down){  }
	else if (left && right){  }
	else if (up && left){ dir = CHARACTER_DIRECTION::UP_LEFT; movex(-1); movey(-1); }
	else if (up && right){ dir = CHARACTER_DIRECTION::UP_RIGHT; movex(1); movey(-1); }
	else if (down && left){ dir = CHARACTER_DIRECTION::DOWN_LEFT; movex(-1); movey(1); }
	else if (down && right){ dir = CHARACTER_DIRECTION::DOWN_RIGHT; movex(1); movey(1); }
	else if (left){ dir = CHARACTER_DIRECTION::LEFT; movex(-1); }
	else if (right){ dir = CHARACTER_DIRECTION::RIGHT; movex(1); }
	else if (up){ dir = CHARACTER_DIRECTION::UP; movey(-1); }
	else if (down){ dir = CHARACTER_DIRECTION::DOWN; movey(1); }
}

void Player::AttackEnemy(){
	//in the direction the sprite is facing, do 2 damage right in front
	//if it collides with enemy, damage that enemy?
}