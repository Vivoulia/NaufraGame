#include "Hitbox.h"

Hitbox::Hitbox(int x, int y, int largeur, int hauteur):m_reglagex(x), m_reglagey(y), m_px(0), m_py(0), m_hauteur(hauteur), m_largeur(largeur)
{
	this->setSize(sf::Vector2f(largeur, hauteur));
	this->setFillColor(sf::Color::Transparent);
	this->setOutlineColor(sf::Color::Black);
	this->setOutlineThickness(1.0);
}

void Hitbox::setCoord(int x, int y)
{
	m_px = x+m_reglagex;
	m_py = y+m_reglagey;
	this->setPosition(sf::Vector2f(m_px, m_py));
}