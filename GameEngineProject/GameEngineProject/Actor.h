#pragma once
#include "SpriteHandler.h"
#include <string>

class Actor {
public:
	Actor(SpriteHandler sprite, bool isInteractable, int x, int y);
	~Actor();

	void setSprite(SpriteHandler sprite);

	// Positioning
	void moveAbsolute(int x, int y);
	void moveRelative(int deltaX, int deltaY);

	bool isInteractable(); // returns interactable var
	void toggleInteractable(); // switch between interactable and not interactable

	std::string getName();
	void setName(std::string name);

private:
	SpriteHandler sprite; 

	int x;
	int y;
	std::string name; // identifier
	bool isInteractable; // can we interact with this object/entity?
};