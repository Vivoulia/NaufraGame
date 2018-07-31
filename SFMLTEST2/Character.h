#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "AnimatedSprite.h"

class Character: public AnimatedSprite
{
public:
	Character(std::string texture);
	void update(int xborder, int yborder, float dt);
	sf::Vector2f getPos() const;
	~Character();

private:
	sf::Texture m_texture;
	float m_vmax;
	float m_vx;
	float m_vy;
	float m_px;
	float m_py;
};

