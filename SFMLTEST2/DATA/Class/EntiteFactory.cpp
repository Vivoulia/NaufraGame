#include "EntiteFactory.h"
#include <iostream>

EntiteFactory::EntiteFactory()
{

}



Entite* EntiteFactory::createEntite(std::string className)
{
	if (className == "Arbre")
	{
		return new Arbre();
	}

	else if (className == "Maison")
	{
		return new Maison();
	}
	else
	{
		std::cout << "ERROR ENTITEFACTORY DECOR INCONNU" << std::endl;
		return NULL;
	}
	
}

Character* EntiteFactory::createCharacter(std::string className)
{
	if (className == "Baba")
	{
		return new Baba();
	}
	else
	{
		std::cout << "ERROR ENTITEFACTORY CHARACTER INCONNU" << std::endl;
		return NULL;
	}
}