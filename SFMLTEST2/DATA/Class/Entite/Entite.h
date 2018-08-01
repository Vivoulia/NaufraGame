#pragma once
#include "../AnimatedSprite.h"
#include "../Hitbox.h"

class Entite : public AnimatedSprite
{
	public:
		Entite(int textRect_width, int textRect_height, int textRect_top, int textRect_left, int hitbox_x, int hitbox_y, int hitbox_largeur, int hitbox_hauteur, std::string texture);
		~Entite();
		Hitbox* getHitBox() const;
	protected:
		sf::Texture m_texture;
		float m_px;
		float m_py;
		Hitbox* hitbox;

};