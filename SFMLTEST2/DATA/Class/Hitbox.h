#pragma once
#include "SFML/Graphics.hpp"

class Hitbox: public sf::RectangleShape
{
public:
	Hitbox(int x, int y, int largeur,int hauteur);
	void setCoord(int x, int y);
protected:
	int m_px; 
	int m_py;
	int m_reglagex;
	int m_reglagey;
	int m_largeur;
	int m_hauteur;
};