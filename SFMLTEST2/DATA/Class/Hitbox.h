#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>

class Hitbox: public sf::RectangleShape
{
public:
	Hitbox(float px, float py, int x, int y, int largeur,int hauteur);
	void setCoord(float x, float y);
	void setBoxSize(int sx, int sy);
	void setPr(float prx, float pry); //changer position relative
	bool intersect(Hitbox* obstacle);
	//sf::Vector2f detailCollision(Hitbox* obstacle);
	float getx();
	float gety();
	float getsizex();
	float getsizey();

protected:
	int m_px; 
	int m_py;
	int m_prx;
	int m_pry;
	int m_sizex;
	int m_sizey;
};