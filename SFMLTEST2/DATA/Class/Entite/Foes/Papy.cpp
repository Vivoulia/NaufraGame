#include "Papy.h"

Papy::Papy(float px, float py): Foes(px, py, 40,40,0,0,0,30,40,15,"DATA/Ressources/Textures/papy_turn_head.png")
{
}

void Papy::update(float dt, sf::Vector2f posJoueur)
{
	if (posJoueur.y > getPosition().y && posJoueur.y < getPosition().y + 300)
	{
		float diff = getPosition().x - posJoueur.x;
		if (diff < 0)
		{
			if (diff < -100) { orient(0); }
			else { orient(1); }
		}
		else
		{
			if (diff > 100) { orient(4); }
			else { orient(3); }
		}
		if (std::abs(diff) < 30) { orient(2); }
	}
	else { orient(2); }
}