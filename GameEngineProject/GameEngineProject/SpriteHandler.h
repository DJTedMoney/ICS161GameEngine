#pragma once
#include <string>
#include <vector>
#include "Sprite.h"

class SpriteHandler
{

public:
	//Might need to have a string as a parameter to know where to look to load sounds
	SpriteHandler();
	~SpriteHandler();

	void makeSprite(Sprite s);
	//Paramater should change based on data structure used
	//Index = index of the sprite on which to call the function
	void displaySprite(int index, int fIndex);
	void displaySprite(int index, std::string seq);
	Sprite getSprite(int index);
	//If it's hit either side of the screen and/or other objects?
	//Call collision class
	void checkCollision(int index);

private:
	std::vector<Sprite> sprites;

};