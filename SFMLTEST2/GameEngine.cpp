#include "GameEngine.h"

GameEngine::GameEngine()
{
	bool mode_dev(true);
	//police d'�criture

	if (!font.loadFromFile("dpcomic.ttf"))
	{
		std::cout << "police introuvable" << std::endl;
	}
}


GameEngine::~GameEngine()
{
}
