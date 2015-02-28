#include "SoundHandler.h"
#include <iostream>


SoundHandler::SoundHandler(std::string musResPath)
{
	MUS_RES_PATH = musResPath;
	int pathSize = MUS_RES_PATH.size();
	
	for (int i = 0; i < pathSize; i++)
	{
		if (MUS_RES_PATH[i] == '\\')
		{
			replace.push_back(i);
		}
	}

	int count = 0;
	for (int i = 0; i < replace.size(); i++)
	{
		
		MUS_RES_PATH.insert(replace[i] + count, "\\");

		count++;
	}
	
	std::cout << "Res Path is: " << MUS_RES_PATH << "\n";
}

SoundHandler::~SoundHandler()
{

}

void SoundHandler::loadSound(std::string fileName, std::string type)
{
	std::string fullPath = MUS_RES_PATH + fileName;
	sound = Mix_LoadWAV(fullPath.c_str());

	std::cout << "The full path: " + fullPath << "\n";

	if (sound == NULL)
	{
		std::cout << fileName << " has NOT been sucessfully loaded." << "\n";
	}
	else
	{
		std::cout << fileName << " has been sucessfully loaded." << "\n";
	}
	

}

void SoundHandler::playSound(std::string toPlay)
{
	Mix_PlayChannel(-1, sound, 0);
}

void SoundHandler::freeMusic()
{
	Mix_FreeChunk(sound);
	sound = NULL;
}

