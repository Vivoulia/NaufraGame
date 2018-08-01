#include "Entite.h"

Entite::Entite(int hitbox_x, int hitbox_y, int hitbox_largeur, int hitbox_hauteur) : m_px(0), m_py(0)
{
	hitbox = new Hitbox(hitbox_x, hitbox_y, hitbox_largeur,  hitbox_hauteur); //20, 50 , 20 , 10
}

Hitbox* Entite::getHitBox() const
{
	return hitbox;
}

Entite::~Entite()
{
	delete hitbox;
}