#pragma once
#include <SDL_image.h>

struct DisplayRenderer
{
	SDL_Texture* texture;
	SDL_Rect src;
	SDL_Rect dst;
};