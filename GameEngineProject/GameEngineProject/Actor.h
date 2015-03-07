#pragma once
#include "Sprite.h"
#include <string>
#include <map>

class Actor {
public:
	Actor(Sprite* sprite, int x, int y, std::string name, bool isInteractable=true);
	~Actor();

	// Sprite
	void setSprite(Sprite* new_sprite);

	// Positioning and Dimensions
	void moveAbsolute(int new_x, int new_y);
	void movex(int delta, const int Screen_height);
	void movey(int delta, const int Screen_height);
	int getX();
	int getY();
	int getWidth();
	int getHeight();

	// Interactability 
	bool isInteractable(); // returns interactable var
	void toggleInteractable(); // switch between interactable and not interactable

	// Identifier
	std::string getName();
	void setName(std::string new_name);

	// Attributes
	void addAttribute(std::string key, std::string value);
	std::string getAttribute(std::string key);
	void removeAttribute(std::string key);

	// AI
	void executeAI( void (*func)() ); // takes function pointer

	// Collision
	bool checkCollision(SDL_Rect& a, SDL_Rect& b);

	//hitbox
	SDL_Rect mColliders;

private:
	Sprite* sprite; 

	std::map<std::string, std::string> attributes; //key-value pairs describing attributes of the actor

	int x;
	int y;
	int width;
	int height;

	std::string name; // identifier
	bool interactable; // can we interact with this object/entity?
};