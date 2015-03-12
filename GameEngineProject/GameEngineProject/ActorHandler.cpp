#include "ActorHandler.h"

ActorHandler::ActorHandler() {}

ActorHandler::~ActorHandler() {
	for (auto it = actors.begin(); it != actors.end(); it++) {
		delete it->second;
	}
}

void ActorHandler::addActor(Sprite* sprite, int x, int y, std::string name, bool isInteractable) {
	Actor* a = new Actor(sprite, x, y, name, isInteractable);
	actors[name] = a;
}

void ActorHandler::removeActor(std::string name) {
	actors.erase(name);
}

void ActorHandler::removeActor(Actor actor) {
	actors.erase(actor.getName());
}

Actor& ActorHandler::getActor(std::string actor_name) {
	return *(actors[actor_name]);
}

std::map<std::string, Actor*> ActorHandler::getAllActors() {
	return actors;
}