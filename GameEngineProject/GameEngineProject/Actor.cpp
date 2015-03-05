#include "Actor.h"

Actor::Actor(SpriteHandler* sprite, bool isInteractable, int x, int y)
:sprite(sprite), interactable(isInteractable), x(x), y(y) {}

Actor::~Actor() {
}

void Actor::setSprite(SpriteHandler* new_sprite) {
	sprite = new_sprite;
}

void Actor::showSprite()
{

}

void Actor::makeFrame()
{

}

void Actor::addFrameToSequence()
{

}

void Actor::moveAbsolute(int new_x, int new_y) {
	x = new_x;
	y = new_y;
}

void Actor::moveRelative(int deltaX, int deltaY) {
	x += deltaX;
	y += deltaY;
}

bool Actor::isInteractable() {
	return interactable;
}

void Actor::toggleInteractable() {
	interactable = !interactable;
}

std::string Actor::getName() {
	return name;
}

void Actor::setName(std::string new_name) {
	name = new_name;
}

void Actor::addAttribute(std::string key, std::string value) {
	attributes[key] = value;
}

std::string Actor::getAttribute(std::string key) {
	return attributes[key];
}

void Actor::removeAttribute(std::string key) {
	attributes.erase(key);
}

void Actor::executeAI(void(*func)()) {

}

void Actor::detectCollision() {

}