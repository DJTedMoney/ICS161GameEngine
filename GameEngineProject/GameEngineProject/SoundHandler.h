#pragma once
#include <string>


class SoundHandler 
{

public:
	//Might need to have a string as a parameter to know where to look to load sounds
	SoundHandler();
	~SoundHandler();

	void playSound(std::string toPlay);
	void setVolume(int volumeLevel);
	void setLoop(bool loop);

private:


};