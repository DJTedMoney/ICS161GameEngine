#pragma once
#include "SpriteHandler.h"
#include <string>
#include <map>

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

	// Attributes
	void addAttribute(std::string key, std::string value);
	std::string getAttribute(std::string key);
	void removeAttribute(std::string key);

private:
	SpriteHandler sprite; 

	std::map<std::string, std::string> attributes; //key-value pairs describing attributes of the actor

	int x;
	int y;
	std::string name; // identifier
	bool isInteractable; // can we interact with this object/entity?
};