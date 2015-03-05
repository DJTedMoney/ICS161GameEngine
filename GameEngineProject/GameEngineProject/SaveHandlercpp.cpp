#include "SaveHandler.h"


SaveHandler* SaveHandler::instance;

SaveHandler* SaveHandler::getInstance()
{
	if (!instance)
		instance = new SaveHandler;
	return instance;
}

//Checks to see if the file can be opened.
bool SaveHandler::open(std::string pathToFile)
{
	file = SDL_RWFromFile(test.c_str(), "r+");

	if (file == NULL)
		std::cout << "Warning: Unable to open file! SDL Error: " << SDL_GetError() << std::endl;

	if (file != NULL)
	{
		std::cout << "New file created!" << std::endl;
		for (int i = 0; i < TOTAL_DATA; ++i)
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
	
	return true;
}

bool SaveHandler::init()
{
	return true;
}

bool SaveHandler::load()
{
	return true;
}

bool SaveHandler::save()
{
	return true;
}

bool SaveHandler::delte()
{
	return true;
}
//Writes string to a file. Doesn't take spaces yet. 
bool SaveHandler::write(std::string toWrite)
{
	file = SDL_RWFromFile(test.c_str(), "w");

	if (file != NULL) 
	{
		size_t len = SDL_strlen(toWrite.c_str());

		if (SDL_RWwrite(file, toWrite.c_str(), 1, len) != len)
		{
			std::cout << "Could not write string!" << std::endl;
		}
		else 
		{
			//printf("Wrote %d 1-byte blocks\n", len);
		}
		SDL_RWclose(file);
	}

	return true;
}