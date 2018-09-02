#pragma once
#include "Foes.h"
#include <iostream>
class Sbire : public Foes
{
public:
	Sbire(float px, float py);
	virtual void update(float dt, sf::Vector2f posJoueur);
protected:
	int m_pos;
	float m_time;
	std::string m_state;
};
