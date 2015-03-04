#include "Sprite.h"

Sprite::Sprite(int width, int height, SDL_Renderer* ren) : width{ width }, height{ height }, renderer{ ren }{



	mColliders.w = width;
	mColliders.h = height;


}



void Sprite ::  setPos(int x, int y){
	this->currX = x;
	this-> currY = y;
}

void Sprite::setColPos(int x, int y){
	this -> mColliders.x = x;
	this -> mColliders.y = y;
}
bool Sprite::checkCollision(SDL_Rect& a, SDL_Rect& b)
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



void Sprite::movex(int delta){
	currX += delta;
}
int Sprite::getWidth(){
	return width;
}
int Sprite::getHeight(){
	return height;
}
void Sprite::movey(int delta){
	currY += delta;
}
int Sprite::getX(){
	return currX;
}

int Sprite::getY(){
	return currY;
}
int  Sprite::makeFrame(SDL_Texture* texture, int x, int y){
	frame fram{ texture, x, y };
	frames.push_back(fram);
	//index start from 0
	return frames.size()-1;
}

int Sprite :: addFrameToSequence(std::string seqName, int frameIndex){
	sequenceList[seqName].push_back(frameIndex);
	return sequenceList.size()-1; 
}



void Sprite::show(int frameIndex){
	SDL_Rect src, dst;

	src.x = frames[frameIndex].x;
	src.y = frames[frameIndex].y;
	src.h = height;
	src.w = width;

	dst.x = currX;
	dst.y = currY;
	dst.w = width; 
	dst.h = height;
	SDL_RenderCopy(this->renderer, frames[frameIndex].texture, &src, &dst);
}

void Sprite::show(std::string sequence){
	if (sequenceIndex < sequenceList[sequence].size()-1){
		show(sequenceList[sequence][sequenceIndex]);
		sequenceIndex++;
	}
	//else if (sequenceList[sequence].size()-1 == sequenceIndex){
	//	show(sequenceList[sequence][0]);
	//}
	else if (sequenceIndex >= (sequenceList[sequence].size())-1){
		sequenceIndex = 0;
		show(sequenceList[sequence][sequenceIndex]);
	}


}