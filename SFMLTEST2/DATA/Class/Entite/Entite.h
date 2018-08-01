#pragma once
#include "../AnimatedSprite.h"
#include "../Hitbox.h"

class Entite : public AnimatedSprite
{
	public:
		Entite(int hitbox_x, int hitbox_y, int hitbox_largeur, int hitbox_hauteur);
		~Entite();
		Hitbox* getHitBox() const;
	protected:
		float m_px;
		float m_py;
		Hitbox* hitbox;

};