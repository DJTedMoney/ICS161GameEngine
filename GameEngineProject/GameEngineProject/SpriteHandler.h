#pragma once
#include <string>

class SpriteHandler
{

public:
	//Might need to have a string as a parameter to know where to look to load sounds
	SpriteHandler();
	~SpriteHandler();

	void makeSprite();
	//Paramater should change based on data structure used
	void displaySprite();
	void moveSprite(int valueToMove);
	//If it's hit either side of the screen and/or other objects?
	//Call collision
	void checkCollision();

private:

};