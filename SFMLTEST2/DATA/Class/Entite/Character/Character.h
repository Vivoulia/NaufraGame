#pragma once
#include "SFML/Graphics.hpp"
#include "../Entite.h"

class Character: public Entite
{
public:
	Character(std::string texture);
	void update(int xborder, int yborder, float dt);
	sf::Vector2f getPos() const;
	~Character();

protected:
	sf::Texture m_texture;
	float m_vmax;
	float m_vx;
	float m_vy;
};

