#include "Entite.h"
#include <iostream>

Entite::Entite(float px, float py, int textRect_width, int textRect_height, int textRect_top, int textRect_left, int hitbox_x, int hitbox_y, int hitbox_largeur, int hitbox_hauteur, std::string texture) : 
	AnimatedSprite(px, py, textRect_width,  textRect_height,  textRect_top,  textRect_left), m_px(px), m_py(py)
{
	hitbox = new Hitbox(px, py, hitbox_x, hitbox_y, hitbox_largeur,  hitbox_hauteur); //20, 50 , 20 , 10
	hurtbox = new Hitbox(px, py, 0, 0, 0, 0);
	hurtbox->setOutlineColor(sf::Color::Red);
	if (!m_texture.loadFromFile(texture))
	{
		std::cout << "mdr ya pas la texture" << std::endl;
	}
	setTexture(m_texture);
	m_px = px;
	m_py = py;
}

Hitbox* Entite::getHitBox() const
{
	return hitbox;
}

Hitbox* Entite::getHurtBox() const
{
	return hurtbox;
}

float Entite::getMaxHealth() const
{
	return m_maxHealth;
}
float Entite::getHealth() const
{
	return m_health;
}
void Entite::setMaxHealth(int maxHealth)
{
	m_maxHealth = maxHealth;
}
void Entite::setHealth(int health)
{
	if (health > m_maxHealth)
	{
		m_health = m_maxHealth;
	}
	else if (health < 0)
	{
		m_health = 0;
	}
	else
	{
		m_health = health;
	}
}

Entite::~Entite()
{
	delete hitbox;
}