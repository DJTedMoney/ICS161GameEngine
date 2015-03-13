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
	for (std::map<std::string, Mix_Music*>::iterator it = musicList.begin(); it != musicList.end(); it++)
	{
		delete it->second;
		musicList.clear();
	}

	for (std::map<std::string, Mix_Chunk*>::iterator it = sfxList.begin(); it != sfxList.end(); it++)
	{
		delete it->second;
		sfxList.clear();
	}

}

void SoundHandler::listenForEvent(SDL_Event e)
{
	if (e.key.keysym.sym == SDLK_1)
	{
		loadSound("05 Intruder 1.mp3", "MUSIC");
		playSound("05 Intruder 1.mp3", "MUSIC");
	}
	else if (e.key.keysym.sym == SDLK_2)
	{
		loadSound("06 Encounter.mp3", "MUSIC");
		playSound("06 Encounter.mp3", "MUSIC");
	}
	else if (e.key.keysym.sym == SDLK_3)
	{
		loadSound("19 VR Training.mp3", "MUSIC");
		playSound("19 VR Training.mp3", "MUSIC");
	}
	else if (e.key.keysym.sym == SDLK_4)
	{

	}
	else if (e.key.keysym.sym == SDLK_5)
	{

	}
}

void SoundHandler::loadSound(std::string fileName, std::string type)
{
	std::string fullPath = MUS_RES_PATH + fileName;

	std::cout << "The full path: " + fullPath << "\n";

	if (type == SFX)
	{
		sfxSound = Mix_LoadWAV(fullPath.c_str());
		sfxList[fileName] = sfxSound;
	}
	else if (type == MUSIC)
	{
		musicSound = Mix_LoadMUS(fullPath.c_str());
		musicList[fileName] = musicSound;
	}

	if (sfxSound == NULL && musicSound == NULL )
	{
		std::cout << fileName << " has NOT been sucessfully loaded." << "\n";
		sfxSound = NULL;
	}
	else
	{
		std::cout << fileName << " has been sucessfully loaded." << "\n";
		musicSound = NULL;
	}



}

void SoundHandler::playSound(std::string toPlay, std::string type)
{
	if (Mix_PlayingMusic() == 0)
	{
		if (type == "SFX")
		{
			Mix_PlayChannel(-1, sfxList[toPlay], 0);
		}
		else if (type == "MUSIC")
		{
			Mix_PlayMusic(musicList[toPlay], -1);
		}
	}

	

}

void SoundHandler::pauseSound()
{
	if (Mix_PlayingMusic)
	{
		Mix_PauseMusic();
	}
}

void SoundHandler::resumeSound()
{
	if (Mix_PausedMusic() == 1)
	{
		Mix_ResumeMusic();
	}
}

void SoundHandler::stopAllSound()
{
	Mix_HaltMusic();
}

void SoundHandler::freeMusic()
{
	Mix_FreeChunk(sfxSound);
	Mix_FreeMusic(musicSound);
	sfxSound = NULL;
	musicSound = NULL;
}

