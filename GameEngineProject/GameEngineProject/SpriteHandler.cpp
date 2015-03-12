#include "SpriteHandler.h"

SpriteHandler::SpriteHandler()
{

}

SpriteHandler::~SpriteHandler()
{

}

void SpriteHandler::makeSprite(Sprite s)
{
	sprites.push_back(s);
}

void SpriteHandler::displaySprite(int index, int fIndex)
{
	sprites[index].show(fIndex);
}

void SpriteHandler::displaySprite(int index, std::string seq)
{
	sprites[index].show(seq);
}

Sprite SpriteHandler::getSprite(int index)
{
	return sprites[index];
}

void SpriteHandler::checkCollision(int index)
{
	//Needs to be fixed
	//sprites[index].checkCollision();
}
