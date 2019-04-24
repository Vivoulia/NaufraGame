#include "Sbire.h"

Sbire::Sbire(float px, float py): Foes(px, py, 50, 50, 0, 0, 10, 0, 30, 20, "DATA/Ressources/Textures/Sbire.png"), m_pos(2), m_time(0), m_state("patrol")
{

}

void Sbire::update(float dt, sf::Vector2f posJoueur)
{
	if (m_state == "patrol")
	{
		m_time += dt;
		if (m_time > 2)
		{
			m_time = 0;
			m_pos += 1;
			if (m_pos == 4) { m_pos = 0; }
			orient(m_pos);
		}
	}
	
}