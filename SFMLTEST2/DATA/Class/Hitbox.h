#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>

class Hitbox: public sf::RectangleShape
{
public:
	Hitbox(float px, float py, int x, int y, int largeur,int hauteur, int hauteurSprite);
	void setCoord(float x, float y);
	void setBoxSize(int sx, int sy);
	void setPr(float prx, float pry); //changer position relative
	bool intersect(Hitbox* obstacle);
	//sf::Vector2f detailCollision(Hitbox* obstacle);
	float getx();
	float gety();
	float getsizex();
	float getsizey();
	sf::Vector2f getCenter();

protected:
	sf::Vector2f m_position;
	int m_prx;
	int m_pry;
	int m_sizex;
	int m_sizey;
	int m_hauteurSprite;
	sf::FloatRect m_boundingBox;
};