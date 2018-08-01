#include "AnimatedSprite.h"
#include <iostream>


AnimatedSprite::AnimatedSprite() : m_time(0), m_rect(0, 128, 64, 64), m_length(64), m_height(64), m_frame(0)
{
	setTextureRect(m_rect);
}

//oriente le personnage (haut : 0, gauche : 1, bas : 2, droite : 3)
void AnimatedSprite::orient(int direction) 
{
	m_rect.top = m_height * direction;
}

//avance l'animation d'une frame et si la boucle est finie, revient à la première frame
void AnimatedSprite::animate(float m_vx, float m_vy, float dt)
{
	if ((m_vx < 10 && m_vx > -10) && (m_vy < 10 && m_vy > -10))
	{
		//std::cout << "freeze ";
		m_time = 0;
		m_frame = 0;
	}
	else
	{
		m_time += dt;
		if (m_time > 0.2)
		{
			m_time = 0;
			m_frame++;

			if (m_frame > 8) //fin du cycle d'animation
			{
				m_frame = 1;
				m_rect.left = m_length;
				std::cout << "next ";
			}
		}
	}
	m_rect.left = m_length * m_frame; 
	std::cout << m_frame << std::endl; //debug
	setTextureRect(m_rect); //mise à jour du sprite
}

AnimatedSprite::~AnimatedSprite()
{
}
