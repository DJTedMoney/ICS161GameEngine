#pragma once
#include <string>

//include SDL2_mixer

class SoundHandler 
{

public:
	//Might need to have a string as a parameter to know where to look to load sounds
	SoundHandler();
	~SoundHandler();

	void loadSound(std::string music);
	void playSound(std::string toPlay);
	void stopSound(std::string toPlay);
	void stopAllSound();
	void setVolume(int volumeLevel, std::string toPlay);
	void setLoop(bool loop, std::string toPlay);

private:
	//Vector or Map to store sound

};