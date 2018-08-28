#pragma once

#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics.hpp"

class AnimatedSprite: public sf::Sprite
{
public:
	AnimatedSprite(float px, float py, int width, int height, int top, int left);
	void animate(float m_vx, float m_vy, float dt);
	void orient(int direction);
	int getHeight() const;
	~AnimatedSprite();

protected:
	sf::IntRect m_rect;
	sf::Sprite m_sprite;
	sf::Sprite* m_pSprite;
	int m_length;
	int m_height;
	int m_frame;
	float m_time;
	std::string m_state;
};
