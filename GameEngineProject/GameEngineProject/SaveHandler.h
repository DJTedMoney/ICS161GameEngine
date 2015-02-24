#pragma once
#include <string>
#include <queue>


class SaveHandler
{

public:
	//Might need to have a string as a parameter to know where to look to load sounds

	static SaveHandler* getInstance();


	bool save();
	bool load();

	bool write();
	bool delte();
	bool open(std::string path);

	void close();

	bool errorExists;

	int gData[10];

private:

	SDL_RWops* file;
	std::string path;
	std::queue<std::string>  eventQueue;

	 static SaveHandler* instance;
	
	 //Singleton class to avoid writing to same file multiple times.
	 SaveHandler(const SaveHandler&);
	 SaveHandler& operator=(const SaveHandler&);
	 SaveHandler() {}
};