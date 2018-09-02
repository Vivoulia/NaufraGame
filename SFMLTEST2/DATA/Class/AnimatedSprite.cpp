#include "AnimatedSprite.h"
#include <iostream>


AnimatedSprite::AnimatedSprite(int textRect_width, int textRect_height, int textRect_top, int textRect_left) : m_time(0), m_rect(textRect_left, textRect_top, textRect_width, textRect_height), m_length(textRect_width), m_height(textRect_height), m_frame(0), m_state("none")
{
	setTextureRect(m_rect);
	this->setOrigin(0, textRect_height);
}

//oriente le personnage (haut : 0, gauche : 1, bas : 2, droite : 3)
void AnimatedSprite::orient(int direction) 
{
	m_rect.top = m_height * direction;
	setTextureRect(m_rect);
}

//avance l'animation d'une frame et si la boucle est finie, revient � la premi�re frame
void AnimatedSprite::animate(float m_vx, float m_vy, float dt)
{
	if (m_state == "walk" || m_state == "none")
	{
		if (m_vx < 0) { m_vx = -m_vx; }
		if (m_vy < 0) { m_vy = -m_vy; }

		if ((m_vx < 10) && (m_vy < 10))
		{
			//std::cout << "freeze ";
			m_time = 0;
			m_frame = 0;
		}
		else
		{
			m_time += dt;
			if (m_time > 7 / (m_vx + m_vy))
			{
				m_time = 0;
				m_frame++;

				if (m_frame > 8) //fin du cycle d'animation
				{
					m_frame = 1;
					m_rect.left = m_length;
					//debug
					//std::cout << "next ";
				}
			}
		}
		m_rect.left = m_length * m_frame;
		setTextureRect(m_rect); //mise � jour du sprite
	}
	else if (m_state == "attack")
	{
		m_time += dt;
		if (m_time > 0.3)
		{
			m_time = 0;
			m_state = "post_attack";
		}
	}
	else if (m_state == "post_attack")
	{
		m_time += dt;
		if (m_time > 0.2)
		{
			m_time = 0;
			m_state = "none";
		}
	}
	
}

int AnimatedSprite::getHeight() const
{
	return m_height;
}

AnimatedSprite::~AnimatedSprite()
{
}


