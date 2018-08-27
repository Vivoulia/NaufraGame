#pragma once
#include "Decor.h"
#include <iostream>

class Papy : public Decor
{
public:
	Papy(float px, float py);
	void update(float dt, sf::Vector2f posJoueur);
};