#pragma once

#include <string>
#include <SDL.h>
#include "SDL_ttf.h"

class UIHandler {

public:
	// make some public stuff
	UIHandler(SDL_Renderer* renderer, std::string fontName, int fontSize = 10, bool visible = true);
	~UIHandler();

	void write(std::string text, int x, int y);

private:
	// make some private stuff
	SDL_Renderer* renderer;

	std::string fontName;
	TTF_Font* font;
	SDL_Color fontColor;
};