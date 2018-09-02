#include "EntiteFactory.h"
#include <iostream>

EntiteFactory::EntiteFactory()
{

}



Entite* EntiteFactory::createEntite(float px, float py, std::string className)
{
	if (className == "Arbre")
	{
		return new Arbre(px, py);
	}

	else if (className == "Maison")
	{
		return new Maison(px, py);
	}
	else if (className == "Echoppe")
	{
		return new Echoppe(px, py);
	}
	else if (className == "Papy")
	{
		return new Papy(px, py);
	}
	else if (className == "Sbire")
	{
		return new Sbire(px, py);
	}
	else
	{
		std::cout << "ERROR ENTITEFACTORY DECOR INCONNU" << std::endl;
		return NULL;
	}
	
}

Character* EntiteFactory::createCharacter(float px, float py, std::string className)
{
	if (className == "Baba")
	{
		return new Baba(px, py);
	}
	else
	{
		std::cout << "ERROR ENTITEFACTORY CHARACTER INCONNU" << std::endl;
		return NULL;
	}
}