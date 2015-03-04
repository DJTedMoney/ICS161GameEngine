#pragma once
#include <string>
#include <queue>
#include "SDL_error.h"
#include "SDL_rwops.h"

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
class SaveHandler
{

public:
	//Might need to have a string as a parameter to know where to look to load sounds
	const int TOTAL_DATA = 10;
	static SaveHandler* getInstance();

	//"C:\\Users\\Hector\\Desktop\\161\\FileToLoad\\"
	std::string test = "C:\\Users\\Hector\\Desktop\\161\\FileToLoad\\sample.txt";


	bool save();
	bool load();

	bool init();
	bool write(std::string toWrite);
	bool delte();
	bool open(std::string path);
	SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren);
	void close();

	bool errorExists;

	int gData[10];
	std::string path;
	SDL_RWops* file;

private:	
	 //Singleton class to avoid writing to same file multiple times.
	 SaveHandler(const SaveHandler&);
	 SaveHandler& operator=(const SaveHandler&);
	 SaveHandler() {};
	 static SaveHandler* instance;
};