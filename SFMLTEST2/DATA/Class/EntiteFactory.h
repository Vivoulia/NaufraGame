#pragma once
#include <string>
#include "Entite/Character/Baba.h"
#include "Entite/Decors/Arbre.h"
#include "Entite/Decors/Maison.h"

class EntiteFactory
{
	public:
		EntiteFactory();
		static Entite* createEntite(std::string className);
		static Character* createCharacter(std::string className);

	private:
};