#pragma once
#include <string>
#include "SDL_mixer.h"
#include <map>
#include <vector>

class SoundHandler 
{

public:
	//Might need to have a string as a parameter to know where to look to load sounds
	SoundHandler(std::string musResPath);
	~SoundHandler(void);


	void loadSound(std::string fileName, std::string type);
	void playSound(std::string toPlay);
	//void stopSound(std::string toPlay);
	//void stopAllSound();
	//void setVolume(int volumeLevel, std::string toPlay);
	//void setLoop(bool loop, std::string toPlay);
	void freeMusic();
	

private:
	//Use Map to store sound
	//resource path
	std::string MUS_RES_PATH;
	char MUS_FILE_PATH;
	std::vector<int> replace;

	Mix_Chunk *sound = NULL;

	//std::map<std::string, Mix_Chunk> sfxList;
	//std::map<std::string, Mix_Music> musicList;
	

};