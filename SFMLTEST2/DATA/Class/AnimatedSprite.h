#pragma once

#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics.hpp"

class AnimatedSprite: public sf::Sprite
{
public:
	AnimatedSprite(int width, int height, int top, int left);
	void animate(float m_vx, float m_vy, float dt);
	void orient(int direction);
	~AnimatedSprite();

protected:
	sf::IntRect m_rect;
	sf::Sprite m_sprite;
	sf::Sprite* m_pSprite;
	int m_length;
	int m_height;
	int m_frame;
	float m_time;
};
