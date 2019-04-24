#include "Hitbox.h"

Hitbox::Hitbox(float px, float py, int x, int y, int largeur, int hauteur, int hauteurSprite):m_prx(x), m_pry(y), m_position(px,py), m_sizex(largeur), m_sizey(hauteur), m_hauteurSprite(hauteurSprite)
{
	//parametrage du rectangle affichable
	this->setSize(sf::Vector2f(m_sizex, m_sizey));
	this->setFillColor(sf::Color(231, 20, 1, 100));
	this->setOutlineColor(sf::Color::Black);
	this->setOutlineThickness(1.0);
	this->setOrigin(sf::Vector2f(0, hauteur));
	m_position.x = px + m_prx;
	m_position.y = py - m_pry;
	setPosition(sf::Vector2f(m_position.x, m_position.y));
}

void Hitbox::setCoord(float x, float y)
{
	m_position.x = x + m_prx;
	m_position.y = y - m_pry;
	setPosition(sf::Vector2f(m_position.x, m_position.y));
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
	//miskine en fait y'a déjà une fonction SFML qui fait ca mieux.
	Hitbox o(*obstacle);
	if ((o.getx() >= m_position.x + m_sizex)      // trop à droite
		|| (o.getx() + o.getsizex() <= m_position.x) // trop à gauche
		|| (o.gety() >= gety() + m_sizey) // trop en bas
		|| (o.gety() + o.getsizey() <= gety()))  // trop en haut
		return false;
	else
		return true;
}

float Hitbox::getx()
{
	return m_position.x;
}

float Hitbox::gety()
{
	return m_position.y - m_hauteurSprite;
}

float Hitbox::getsizex()
{
	return m_sizex;
}

float Hitbox::getsizey()
{
	return m_sizey;
}

sf::Vector2f Hitbox::getCenter()
{
	m_boundingBox = getGlobalBounds();
	return sf::Vector2f(m_boundingBox.left+ (m_boundingBox.width/2), m_boundingBox.top + (m_boundingBox.height/2));
}