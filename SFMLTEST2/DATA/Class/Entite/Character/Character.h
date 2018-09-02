#pragma once
#include "SFML/Graphics.hpp"
#include "../Entite.h"
#include <iostream>

class Character: public Entite
{
public:
	Character(float px, float py, int textRect_width, int textRect_height, int textRect_top, int textRect_left, int hitbox_x, int hitbox_y, int hitbox_largeur, int hitbox_hauteur, std::string texture);
	void update(int xborder, int yborder, float dt, std::vector<Entite*>& allEntite);
	sf::Vector2f getPos() const;
	sf::Vector2f getCenter() const;
	void attack(sf::Vector2f vect);
	void setMode(std::string mode);
	std::string getMode();
	~Character();

protected:
	sf::Texture m_texture;
	float m_acc; //acc�l�ration
	float m_vmax; //vitesse de pointe
	float m_vx; //vitesse en x
	float m_vy; //vitesse en y
	float m_spx; //save posx
	float m_spy; //save poy
	std::string m_mode; //combat ou exploration
	sf::Vector2f m_walkInput;
};

