#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "SFML/Graphics/Sprite.hpp"
#include <string>

class AnimatedSprite: public sf::Sprite
{
public:
	AnimatedSprite();
	void animate(float m_vx, float m_vy, float dt);
	void orient(int direction);
	~AnimatedSprite();

private:
	sf::IntRect m_rect;
	sf::Sprite m_sprite;
	sf::Sprite* m_pSprite;
	int m_length;
	int m_height;
	int m_frame;
	float m_time;
};
