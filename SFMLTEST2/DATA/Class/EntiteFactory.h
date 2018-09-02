#pragma once
#include <string>

/*CHARACTER*/
#include "Entite/Character/Baba.h"

/* DECOR */
#include "Entite/Decors/Arbre.h"
#include "Entite/Decors/Maison.h"
#include "Entite/Decors/Echoppe.h"

/* FOES */
#include "Entite/Foes/Papy.h"
#include "Entite/Foes/Sbire.h"


class EntiteFactory
{
	public:
		EntiteFactory();
		static Entite* createEntite(float px, float py, std::string className);
		static Character* createCharacter(float px, float py, std::string className);

	private:
};