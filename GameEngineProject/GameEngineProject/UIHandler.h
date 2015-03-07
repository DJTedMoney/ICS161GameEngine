#pragma once


#include <SDL.h>
#include "SDL_ttf.h"

// for the timer
#include <iostream>
#include <ctime>
#include <cstdlib>

class UIHandler {

public:
	// make some public stuff
	
	UIHandler(SDL_Renderer* renderer, std::string fontName, int fontSize);
	~UIHandler();

	// for simply writing stuff on the screen
	SDL_Texture* loadText(const std::string &file, SDL_Renderer *ren);
	void renderText(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h);
	void renderText(SDL_Texture *tex, SDL_Renderer *ren, int x, int y);
	void write(std::string text, int x, int y, SDL_Color c);

	void timerStuff();
	//std::string &fontFile, int size, SDL_Renderer *r

	clock_t timer;

	SDL_Texture* getClock();
	SDL_Renderer* getRenderer();


private:
	// make some private stuff
	SDL_Renderer* renderer;
	SDL_Texture* texture;
	SDL_Surface* surface;


	std::string fontName;
	TTF_Font* font;
	SDL_Color fontColor;
	int fontSize;
};

// some advice:
// game state in another class 
// different elements as different classes as well
// update method -- thought of that