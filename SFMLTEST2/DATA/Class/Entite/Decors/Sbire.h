#pragma once
#include "Decor.h"
#include <iostream>
class Sbire : public Decor
{
public:
	Sbire(float px, float py);
	void update(float dt, sf::Vector2f posJoueur);
protected:
	int m_pos;
	float m_time;
	std::string m_state;
};
