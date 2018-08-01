#include "Entite.h"
#include <iostream>

Entite::Entite(int textRect_width, int textRect_height, int textRect_top, int textRect_left, int hitbox_x, int hitbox_y, int hitbox_largeur, int hitbox_hauteur, std::string texture) :
	AnimatedSprite( textRect_width,  textRect_height,  textRect_top,  textRect_left), m_px(0), m_py(0)
{
	hitbox = new Hitbox(hitbox_x, hitbox_y, hitbox_largeur,  hitbox_hauteur); //20, 50 , 20 , 10

	if (!m_texture.loadFromFile(texture))
	{
		std::cout << "mdr ya pas la texture" << std::endl;
	}
	setTexture(m_texture);
}

Hitbox* Entite::getHitBox() const
{
	return hitbox;
}

Entite::~Entite()
{
	delete hitbox;
}