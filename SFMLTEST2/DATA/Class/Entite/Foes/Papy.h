#pragma once
#include "Foes.h"
#include <iostream>

class Papy : public Foes
{
public:
	Papy(float px, float py);
	virtual void update(float dt, sf::Vector2f posJoueur);
};