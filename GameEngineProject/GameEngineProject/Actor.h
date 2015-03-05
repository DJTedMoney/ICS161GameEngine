#pragma once
#include "SpriteHandler.h"
#include <string>
#include <map>

class Actor {
public:
	Actor(SpriteHandler* sprite, bool isInteractable, int x, int y);
	~Actor();

	// Sprite
	void setSprite(SpriteHandler* new_sprite);
	void showSprite();
	void makeFrame();
	void addFrameToSequence();


	// Positioning
	void moveAbsolute(int new_x, int new_y);
	void moveRelative(int deltaX, int deltaY);

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
	void detectCollision();

private:
	SpriteHandler* sprite; 

	std::map<std::string, std::string> attributes; //key-value pairs describing attributes of the actor

	int x;
	int y;
	std::string name; // identifier
	bool interactable; // can we interact with this object/entity?
};