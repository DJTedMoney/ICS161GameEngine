#include "Actor.h"

Actor::Actor(Sprite* sprite, int x, int y, std::string name, bool interActable)
	:sprite(sprite), interactable(interActable), x(x), y(y), name(name)
{
	mColliders.w = width;
	mColliders.h = height;
}

Actor::Actor(int x, int y, std::string name, bool isInteractable)
:interactable(isInteractable), x(x), y(y), name(name) {
	mColliders.w = width;
	mColliders.h = height;
}
	
Actor::~Actor() {
}

void Actor::setSprite(Sprite* new_sprite) {
	sprite = new_sprite;
}

void Actor::moveAbsolute(int new_x, int new_y) {
	x = new_x;
	y = new_y;
}

void Actor::movey(int delta, const int Screen_height){
	y += delta;
	mColliders.y = y;
	if ((y < 0) || (y + height > Screen_height)  ){
		movey(-delta, Screen_height);
		mColliders.y = y;
	}
}

void Actor::movex(int delta, const int Screen_width){
	x += delta;
	mColliders.x = x;
	if ((x < 0) || (x + width > Screen_width) ){
		movex(-delta, Screen_width);
		mColliders.x = x;
	}
}

int Actor::getX() {
	return x;
}

int Actor::getY() {
	return y;
}

int Actor::getWidth(){
	return width;
}
int Actor::getHeight(){
	return height;
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

bool Actor::checkCollision(SDL_Rect& a, SDL_Rect& b)
{
		//The sides of the rectangles
		int leftA, leftB;
		int rightA, rightB;
		int topA, topB;
		int bottomA, bottomB;

		//Calculate the sides of rect A
		leftA = a.x;
		rightA = a.x + a.w;
		topA = a.y;
		bottomA = a.y + a.h;

		//Calculate the sides of rect B
		leftB = b.x;
		rightB = b.x + b.w;
		topB = b.y;
		bottomB = b.y + b.h;

		//If any of the sides from A are outside of B
		if (bottomA <= topB)
		{
			return false;
		}

		if (topA >= bottomB)
		{
			return false;
		}

		if (rightA <= leftB)
		{
			return false;
		}

		if (leftA >= rightB)
		{
			return false;
		}

		//If none of the sides from A are outside B
		return true;
}