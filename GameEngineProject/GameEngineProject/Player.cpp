#include "Player.h"

//need to add a check: for LR, if previous was U/D, then combine. And vice versa.
void Player::PlayerInput(){
	
	

	SDL_Event e;
	SDL_PollEvent(&e);


	//there's probably a better way to do this:
		//if (w key down && d key down) direction = up right, moveCharacter(1, -1))
	if (e.type == SDL_KEYDOWN){
		switch (e.key.keysym.sym){
		
		//left
		case SDLK_a:
			if (this->dir == CHARACTER_DIRECTION::UP){ this->dir = CHARACTER_DIRECTION::UP_LEFT; }
			else if (this->dir == CHARACTER_DIRECTION::DOWN){ this->dir = CHARACTER_DIRECTION::DOWN_LEFT; }
			else{ this->dir == CHARACTER_DIRECTION::LEFT; }
			this->movex(-1);
			break;
		
		//right
		case SDLK_d:
			if (this->dir == CHARACTER_DIRECTION::UP){ this->dir = CHARACTER_DIRECTION::UP_RIGHT; }
			else if (this->dir == CHARACTER_DIRECTION::DOWN){ this->dir = CHARACTER_DIRECTION::DOWN_RIGHT; }
			else{ this->dir == CHARACTER_DIRECTION::RIGHT; }
			this->movex(1);
			break;
		
		//up
		case SDLK_w:
			if (this->dir == CHARACTER_DIRECTION::LEFT){ this->dir = CHARACTER_DIRECTION::UP_LEFT; }
			else if (this->dir == CHARACTER_DIRECTION::RIGHT){ this->dir = CHARACTER_DIRECTION::UP_RIGHT; }
			else{ this->dir == CHARACTER_DIRECTION::UP; }
			this->movey(-1);
			break;
		
		//down
		case SDLK_s:
			if (this->dir == CHARACTER_DIRECTION::LEFT){ this->dir = CHARACTER_DIRECTION::DOWN_LEFT; }
			else if (this->dir == CHARACTER_DIRECTION::RIGHT){ this->dir = CHARACTER_DIRECTION::DOWN_RIGHT; }
			else{ this->dir == CHARACTER_DIRECTION::DOWN; }
			this->movey(1);
			break;


		case SDLK_SPACE:
			AttackEnemy();
			break;
		default:
			break;
		}
	}
}

void Player::AttackEnemy(){
	//in the direction the sprite is facing, do 2 damage right in front
	//if it collides with enemy, damage that enemy?
}