#include <SDL.h>
#include <SDL_mixer.h>
#include "res_path.h"
#include "cleanup.h"
#include "SDL_image.h"
#include "Sprite.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//added sound support using SDL_mixer press 9 to play the sounds
/**
* Log an SDL error with some error message to the output stream of our choice
* @param os The output stream to write the message to
* @param msg The error message to write, format will be msg error: SDL_GetError()
*/
void logSDLError(std::ostream &os, const std::string &msg){
	os << msg << " error: " << SDL_GetError() << std::endl;
	/*std::ostringstream errMsg;
	errMsg << " error: " << SDL_GetError() << std::endl;
	OutputDebugString(errMsg.str().c_str());*/
}

/**
* Loads an image into a texture on the rendering device
* @param file The image file to load
* @param ren The renderer to load the texture onto
* @return the loaded texture, or nullptr if something went wrong.
*/
SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren){
	SDL_Texture *texture = IMG_LoadTexture(ren, file.c_str());
	if (texture == nullptr){
		logSDLError(std::cout, "LoadTexture");
	}
	return texture;
}


int main(int argc, char **argv){

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		SDL_Quit();
		return 1;
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		SDL_Quit();
		return 1;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
//		std::ostringstream debugMsg;
		//debugMsg << "SDL_Init Error: " << SDL_GetError() << std::endl;
		//OutputDebugString(debugMsg.str().c_str());
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG){
		logSDLError(std::cout, "IMG_Init");
		SDL_Quit();
		return 1;
	}

	SDL_Window *window = SDL_CreateWindow("Sprite Demo", 800, 100, SCREEN_WIDTH,
		SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == nullptr){
		logSDLError(std::cout, "CreateWindow");
		SDL_Quit();
		return 1;
	}
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr){
		logSDLError(std::cout, "CreateRenderer");
		cleanup(window);
		SDL_Quit();
		return 1;
	}

	const std::string resPath = getResourcePath("SpriteDemo");
	// background is from "iceland1.jpg" at theadventurousmailbox.com
	SDL_Texture *background = loadTexture(resPath + "Background.png", renderer);
	//Make sure all is well
	if (background == nullptr){
		cleanup(background, renderer, window);
		IMG_Quit();
		SDL_Quit();
		return 1;
	}
	//The music that will be played
	Mix_Music *gMusic = NULL;
	gMusic = Mix_LoadMUS((resPath + "beat.wav").c_str());
	if (gMusic == NULL)
	{
		printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
		Mix_Quit();
		IMG_Quit();
		SDL_Quit();
		return 1;
	}
	Sprite* spriteBG = new Sprite(SCREEN_WIDTH, SCREEN_HEIGHT, renderer);
	spriteBG->setPos(0, 0);
	int bgFrame = spriteBG->makeFrame(background, 0, 0);

	SDL_Texture *spritesheet4 = loadTexture(resPath + "box.png", renderer);
	SDL_Texture *spritesheet = loadTexture(resPath + "player.png", renderer);
	// spritesheet is from "player.png" at www.briancollins1.com
	if (spritesheet == nullptr){
		cleanup(spritesheet, renderer, window);
		IMG_Quit();
		SDL_Quit();
		return 1;
	}

	SDL_Texture *spritesheet2 = loadTexture(resPath + "Up.png", renderer);
	if (spritesheet2 == nullptr){
		cleanup(spritesheet2, renderer, window);
		IMG_Quit();
		SDL_Quit();
		return 1;
	}

	SDL_Texture *spritesheet3 = loadTexture(resPath + "Down.png", renderer);
	if (spritesheet3 == nullptr){
		cleanup(spritesheet3, renderer, window);
		IMG_Quit();
		SDL_Quit();
		return 1;
	}

	Sprite* sprite1 = new Sprite(60, 50, renderer);
	Sprite* sprite2 = new Sprite(60, 50, renderer);
	sprite2->addFrameToSequence("walk left", sprite2->makeFrame(spritesheet4, 50, 50));
	sprite2->addFrameToSequence("walk right", sprite2->makeFrame(spritesheet4, 50, 50));
	sprite2->addFrameToSequence("float up", sprite2->makeFrame(spritesheet4, 50, 50));
	sprite2->addFrameToSequence("float down", sprite2->makeFrame(spritesheet4, 50, 50));

	sprite1->addFrameToSequence("walk right", sprite1->makeFrame(spritesheet, 217, 20));
	sprite1->addFrameToSequence("walk right", sprite1->makeFrame(spritesheet, 310, 20));
	sprite1->addFrameToSequence("walk right", sprite1->makeFrame(spritesheet, 418, 20));
	sprite1->addFrameToSequence("walk right", sprite1->makeFrame(spritesheet, 515, 20));
	//sprite1->addFrameToSequence("walk right", sprite1->makeFrame(spritesheet, 1210, 20));
	//sprite1->addFrameToSequence("walk right", sprite1->makeFrame(spritesheet, 1510, 0));
	//sprite1->addFrameToSequence("walk right", sprite1->makeFrame(spritesheet, 570, 0));

	sprite1->addFrameToSequence("walk left", sprite1->makeFrame(spritesheet2, 750, 20));
	sprite1->addFrameToSequence("walk left", sprite1->makeFrame(spritesheet2, 650, 20));
	sprite1->addFrameToSequence("walk left", sprite1->makeFrame(spritesheet2, 565, 20));
	sprite1->addFrameToSequence("walk left", sprite1->makeFrame(spritesheet, 455, 20));
	//sprite1->addFrameToSequence("walk left", sprite1->makeFrame(spritesheet, 1210, 295));
	sprite1->addFrameToSequence("float up", sprite1->makeFrame(spritesheet2, 345, 345));
	sprite1->addFrameToSequence("float up", sprite1->makeFrame(spritesheet2, 235, 345));
	sprite1->addFrameToSequence("float up", sprite1->makeFrame(spritesheet2, 345, 345));
	//for (int i = 0; i<13; i++)
	//{
	//	for (int j = 0; j<5; j++)
	//	{
	//		sprite1->addFrameToSequence("float down", sprite1->makeFrame(spritesheet3, 0, i * 130));
	//	}
	//}
	sprite1->addFrameToSequence("float down", sprite1->makeFrame(spritesheet2, 340, 20));
	sprite1->addFrameToSequence("float down", sprite1->makeFrame(spritesheet2, 340, 100));
	sprite1->addFrameToSequence("float down", sprite1->makeFrame(spritesheet2, 340, 180));
	int x = SCREEN_WIDTH / 2;
	int y = SCREEN_HEIGHT / 2;
	sprite1->setPos(x, y);
	sprite1->setColPos(x, y);
	sprite2->setPos(50, 50);
	sprite2->setColPos(50, 50);

	SDL_Event e;
	bool quit = false;
	std::string spriteDirection = "float up";
	while (!quit){
		while (SDL_PollEvent(&e)){
			if (e.type == SDL_QUIT){
				quit = true;
			}
			if (e.type == SDL_KEYDOWN){
				if (e.key.keysym.sym == SDLK_RIGHT)
				{
					sprite1->movex(5);
					sprite1->mColliders.x = sprite1->getX();
					if ((sprite1->getX() < 0) || (sprite1->getX() + sprite1->getWidth() > SCREEN_WIDTH) || sprite1->checkCollision(sprite1-> mColliders, sprite2-> mColliders)){
						sprite1->movex(-5);
						sprite1->mColliders.x = sprite1->getX();
					}
					spriteDirection = "walk right";
				}
				else if (e.key.keysym.sym == SDLK_LEFT)
				{
					sprite1->movex(-5);
					sprite1->mColliders.x = sprite1->getX();
					if ((sprite1->getX() < 0) || (sprite1->getX() + sprite1->getWidth() > SCREEN_WIDTH) || sprite1->checkCollision(sprite1->mColliders, sprite2->mColliders)){
						sprite1->movex(5);
						sprite1->mColliders.x = sprite1->getX();
					}
					spriteDirection = "walk left";
				}
				else if (e.key.keysym.sym == SDLK_UP)
				{
					sprite1->movey(-5);
					sprite1->mColliders.y = sprite1->getY();
					if ((sprite1->getY() < 0) || (sprite1->getY() + sprite1->getHeight() > SCREEN_HEIGHT) || sprite1->checkCollision(sprite1->mColliders, sprite2->mColliders)){
						sprite1->movey(5);
						sprite1->mColliders.y = sprite1->getY();
					}
					spriteDirection = "float up";
				}
				else if (e.key.keysym.sym == SDLK_DOWN)
				{
					sprite1->movey(5);
					sprite1->mColliders.y = sprite1->getY();
					if ((sprite1->getY() < 0) || (sprite1->getY() + sprite1->getHeight() > SCREEN_HEIGHT) || sprite1->checkCollision(sprite1->mColliders, sprite2->mColliders)){
						sprite1->movey(-5);
						sprite1->mColliders.y = sprite1->getY();
					}

					spriteDirection = "float down";
				}
			}
		}
		//Render the scene
	

		SDL_RenderClear(renderer);
		spriteBG->show(bgFrame);
		sprite1->show(spriteDirection.c_str());
		sprite2->show(spriteDirection.c_str());
		SDL_RenderPresent(renderer);
	}
	//Free the music
	Mix_FreeMusic(gMusic);
	gMusic = NULL;
	cleanup(background, spritesheet, spritesheet2, spritesheet3, renderer, window);
	IMG_Quit();
	SDL_Quit();


	return 0;
}
