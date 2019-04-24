#include "Entite.h"
#include <iostream>

Entite::Entite(float px, float py, int textRect_width, int textRect_height, int textRect_top, int textRect_left, int hitbox_x, int hitbox_y, int hitbox_largeur, int hitbox_hauteur, std::string texture) :
	AnimatedSprite(textRect_width,  textRect_height,  textRect_top,  textRect_left), m_position(px,py),  m_speed(0,0)
{
	hitbox = new Hitbox(px, py, hitbox_x, hitbox_y, hitbox_largeur,  hitbox_hauteur, textRect_height); //20, 50 , 20 , 10
	hurtbox = new Hitbox(px, py, 0, 0, 0, 0, textRect_height);
	hurtbox->setOutlineColor(sf::Color::Red);
	if (!m_texture.loadFromFile(texture))
	{
		std::cout << "mdr ya pas la texture" << std::endl;
	}
	setTexture(m_texture);
	this->setOrigin(0, textRect_height);//peut être redondant avec Animated sprite ?
	this->setPosition(px, py);
	m_center.x = px + (m_height / 2);
	m_center.y = py + (m_length / 2);
}

void Entite::update(float dt, sf::Vector2f posJoueur)
{

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

sf::Vector2f Entite::getPos() const
{
	return sf::Vector2f(m_position.x, m_position.y);
}

void Entite::setZorder(int zorder)
{
	m_zorder = zorder;
}

int Entite::getZorder() const
{
	return m_zorder;
}

sf::Vector2f Entite::getCenter()
{
	setCenter(m_position.x, m_position.y);
	return m_center;
}

void Entite::setCenter(float px, float py)
{
	m_center.x = px + (m_height / 2);
	m_center.y = py - (m_length / 2);
}

sf::Vector2f Entite::makeVector(sf::Vector2f vector1, sf::Vector2f vector2)
{
	return sf::Vector2f(vector1.x - vector2.x, vector1.y - vector2.y);
}

sf::Vector2f Entite::unify(sf::Vector2f vect)
{
	sf::Vector2f vect_base;
	//création du vecteur unitaire
	if (std::abs(vect.x) > std::abs(vect.y))
	{
		vect_base.y = std::abs(vect.y / vect.x);
		if (vect.y < 0) { vect_base.y *= -1; }
		if (vect.x < 0) { vect_base.x = -1; }
		else { vect_base.x = 1; }
	}
	else
	{
		vect_base.x = std::abs(vect.x / vect.y);
		if (vect.x < 0) { vect_base.x *= -1; }
		if (vect.y < 0) { vect_base.y = -1; }
		else { vect_base.y = 1; }
	}
	return vect_base;
}

sf::Vector2f Entite::multiply(sf::Vector2f vector, float facteur)
{
	return sf::Vector2f(vector.x * facteur, vector.y * facteur);
}

void Entite::applyVector(sf::Vector2f vector)
{
	m_speed.x += vector.x;
	m_speed.y += vector.y;
}

void Entite::applySpeed(float dt)
{
	//reposionnement de l'entité (+= vitesse*temps)
	m_position.x += m_speed.x * dt;
	m_position.y += m_speed.y * dt;
}

Entite::~Entite()
{
	delete hitbox;
}