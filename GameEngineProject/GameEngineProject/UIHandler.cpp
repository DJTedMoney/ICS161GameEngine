#include <iostream>
#include <sstream>
#include <SDL.h>
#include "SDL_image.h"
#include "Windows.h"
#include "UIHandler.h"

UIHandler::UIHandler(SDL_Renderer* r, std::string fn, int fs) {
	TTF_Init();

	renderer = r;
	fontName = fn;
	fontSize = fs;

	font = TTF_OpenFont(fontName.c_str(), fs);
	if (font == nullptr){
		std::cout << "TTF_OpenFont failed!" << std::endl;
	}
}

UIHandler::~UIHandler() {
	TTF_CloseFont(font);
	TTF_Quit();
	SDL_FreeSurface(surface);
}

void UIHandler::write(std::string text, int x, int y, SDL_Color c) {
	int width;
	int height;
	TTF_SizeText(font, text.c_str(), &width, &height);

	surface = TTF_RenderText_Blended(font, text.c_str(), c);

	texture = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_Rect dest;
	dest.x = x;
	dest.y = y;
	SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
	SDL_RenderCopy(renderer, texture, NULL, &dest);
}

SDL_Texture* UIHandler::loadText(const std::string &file, SDL_Renderer *ren) {
	SDL_Texture *texture = IMG_LoadTexture(ren, file.c_str());
	if (texture == nullptr){
		std::cout << "Texture is null!" << std::endl;
	}
	return texture;
}


void UIHandler::renderText(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h){
	//Setup the destination rectangle to be at the position we want
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	dst.w = w;
	dst.h = h;
	SDL_RenderCopy(ren, tex, NULL, &dst);
}

void UIHandler::renderText(SDL_Texture *tex, SDL_Renderer *ren, int x, int y) {
	int w, h;
	SDL_QueryTexture(tex, NULL, NULL, &w, &h);
	renderText(tex, ren, x, y, w, h);
}
