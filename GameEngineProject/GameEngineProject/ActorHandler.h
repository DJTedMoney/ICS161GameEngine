#pragma once
#include "Actor.h"
#include <map>
#include <vector>
#include <string>
#include "SpriteHandler.h"
class ActorHandler {
public:
	ActorHandler();
	~ActorHandler();

	void addActor(Sprite* sprite, int x, int y, std::string name, bool isInteractable);

	void removeActor(std::string name); // remove with actor's name
	void removeActor(Actor actor);	// remove by retrieving actor's name from actor

	Actor& getActor(std::string actor_name); // returns reference to the actor

private:
	std::map<std::string, Actor*> actors; // actor name (identifier) is the same as the key
};