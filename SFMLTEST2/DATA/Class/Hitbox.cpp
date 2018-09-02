#include "Hitbox.h"

Hitbox::Hitbox(float px, float py, int x, int y, int largeur, int hauteur, int hauteurSprite):m_prx(x), m_pry(y), m_px(0), m_py(0), m_sizex(largeur), m_sizey(hauteur), m_hauteurSprite(hauteurSprite)
{
	this->setSize(sf::Vector2f(largeur, hauteur));
	this->setFillColor(sf::Color::Transparent);
	this->setOutlineColor(sf::Color::Black);
	this->setOutlineThickness(1.0);
	m_px = px + m_prx;
	m_py = py + m_pry - m_hauteurSprite;
	setPosition(sf::Vector2f(m_px, m_py));
}

void Hitbox::setCoord(float x, float y)
{
	m_px = x + m_prx;
	m_py = y + m_pry - m_hauteurSprite;
	setPosition(sf::Vector2f(m_px, m_py));
}

void Hitbox::setBoxSize(int sx, int sy)
{
	m_sizex = sx;
	m_sizey = sy;
	setSize(sf::Vector2f(m_sizex, m_sizey));
}

void Hitbox::setPr(float prx, float pry)
{
	m_prx = prx;
	m_pry = pry;
}

bool Hitbox::intersect(Hitbox* obstacle)
{
	Hitbox o(*obstacle);
	if ((o.getx() >= m_px + m_sizex)      // trop à droite
		|| (o.getx() + o.getsizex() <= m_px) // trop à gauche
		|| (o.gety() >= m_py + m_sizey) // trop en bas
		|| (o.gety() + o.getsizey() <= m_py))  // trop en haut
		return false;
	else
		return true;

}
/*
sf::Vector2f Hitbox::detailCollision(Hitbox* obstacle)
{
	Hitbox o(*obstacle);
	//on teste les coins un par un
	//haut à gauche
	if (m_px < o.getx() + o.getsizex() && m_px > o.getx())
	{
		if (m_py > o.gety() + o.getsizey())
		{
			return sf::Vector2f(0, 1);
		}
	}
	if (m_py < o.gety() + o.getsizey() && m_py > o.gety())
	{
		if (m_px > o.getx() + o.getsizex())
		{
			return sf::Vector2f(1, 0);
		}

	}
	//haut à droite
	else if (m_px + m_sizex < o.getx() + o.getsizex() && m_px + m_sizex > o.getx() 
		&& m_py < o.gety() + o.getsizey() && m_py > o.gety())
	{
		return true;
	}
	//bas à droite
	else if (m_px + m_sizex < o.getx() + o.getsizex() && m_px + m_sizex > o.getx() 
		&& m_py + m_sizey < o.gety() + o.getsizey() && m_py + m_sizey > o.gety())
	{
		return true;
	}
	//bas à gauche
	else if (m_px < o.getx() + o.getsizex() && m_px > o.getx() 
		&& m_py + m_sizey < o.gety() + o.getsizey() && m_py + m_sizey > o.gety())
	{
		return true;
	}
	//pas de collision
	else { return false; }
}
*/

float Hitbox::getx()
{
	return m_px;
}

float Hitbox::gety()
{
	return m_py;
}
float Hitbox::getsizex()
{
	return m_sizex;
}
float Hitbox::getsizey()
{
	return m_sizey;
}