#pragma once

#include "SDL.h"
#include <vector>
#include <map>
#include <iostream>
#include "RenderStruct.h"

class Sprite
{
public:
	Sprite(int width, int height, SDL_Renderer* ren);
	//hitbox
	SDL_Rect mColliders;
	//new constructor with a rotation degree parameter
	~Sprite();

	void setPos(int x, int y);
	void movex(int delta);
	void movey(int delta);
	int getX();
	int getY();
	int getWidth();
	int getHeight();
	bool checkCollision(SDL_Rect& a, SDL_Rect& b);

	// makeFrame returns the unique index of the frame
	int makeFrame(SDL_Texture* texture, int x, int y);

	// addFrameToSequence returns the number of frames in the sequence after the add
	int addFrameToSequence(std::string seqName, int frameIndex);

	// show(int) renders the frame with the specified frameIndex
	DisplayRenderer show(int frameIndex);
	// show(string) cycles through all frames in the specified sequence, one per call
	DisplayRenderer show(std::string sequence);


// The private part of the class is given as a hint or suggestion.
// In homework 3 you can make any modifications you want to the class's innards.
private:
	int width, height;
	int currX, currY;		// the coordinates of the sprite's upper left hand corner relative to the window
	SDL_Renderer* renderer;
	
	static const int V;

	struct frame
	{
		SDL_Texture* texture;
		int x;
		int y;
	};
	std::vector<frame> frames;

	std::map<std::string, std::vector<int>> sequenceList;
	int sequenceIndex;		// shared by all sequences; it would be better to have
							// one for each sequence
	int sequenceIndex2;

};

