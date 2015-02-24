#include "SaveHandler.h"
#include "SDL_error.h"
#include "SDL_rwops.h"
#include <iostream>

SaveHandler* SaveHandler::instance;



SaveHandler* SaveHandler::getInstance()
{
	if (!instance)
		instance = new SaveHandler;
	return instance;
}

bool SaveHandler::open(std::string pathToFile)
{
	file = SDL_RWFromFile(pathToFile.c_str(), "r+b");

	if (file == NULL)
		std::cout << "Warning: Unable to open file! SDL Error: " << SDL_GetError() << std::endl;

	if (file != NULL)
	{
		std::cout << "New file created!" << std::endl;
		for (int i = 0; i < 10; ++i)
		{
			gData[i] = 0;
			SDL_RWwrite(file, &gData[i], sizeof(Sint32), 1);
		}
		//Close file handler 
		SDL_RWclose(file);
	}
	else
	{
		std::cout << "Error: Unable to create file! SDL Error: " << SDL_GetError() << std::endl;
		errorExists = true;
	}
}


bool SaveHandler::load()
{

}

bool SaveHandler::save()
{

}

bool SaveHandler::delte()
{

}

bool SaveHandler::write()
{

}