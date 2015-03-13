#pragma once
#include "Actor.h"

class TriggerPoint : public Actor{
	//when the player walks over it, spawn enemies
	//that's all it does

public:
	TriggerPoint(std::string name, int x, int y, std::string wts) : Actor(x, y, name, true){ whatToSpawn = wts; }

	std::string whatToSpawn;

	void SpawnEnemy(){
		
		//spawn 2 zerglings
		if (whatToSpawn == "zerglings"){

		}

		//spawn 2 zealots
		else if (whatToSpawn == "zealot"){

		}
	}
};