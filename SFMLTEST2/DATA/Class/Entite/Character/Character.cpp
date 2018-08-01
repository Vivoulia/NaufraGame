#include "Character.h"
#include <iostream>


Character::Character(int textRect_width, int textRect_height, int textRect_top, int textRect_left, int hitbox_x, int hitbox_y, int hitbox_largeur, int hitbox_hauteur, std::string texture) : 
	Entite (textRect_width,  textRect_height,  textRect_top,  textRect_left, hitbox_x,  hitbox_y,  hitbox_largeur,  hitbox_hauteur, texture),  m_vx(0), m_vy(0), m_vmax(75.0)
{

}

//met à jour la position du personnage en fonction de sa vitesse et des évènements clavier
void Character::update(int xborder, int yborder, float dt)
{
	//ralentissement auto (frottements)
	m_vx *= float(0.99);
	m_vy *= float(0.99);
	
	//evenements clavier
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		m_vy -= 10; //acceleration en -y (haut)
		if (m_vy < -m_vmax) { m_vy = -m_vmax; }; //vérification du non dépassement de la vitesse max
		orient(0); //orientation du sprite vers le haut
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		m_vy += 10;
		if (m_vy > m_vmax) { m_vy = m_vmax; };
		orient(2);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		m_vx -= 10;
		if (m_vx < -m_vmax) { m_vx = -m_vmax; };
		orient(1);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		m_vx += 10;
		if (m_vx > m_vmax) { m_vx = m_vmax; };
		orient(3);
	}

	//mise à jour des coordonnées (+= vitesse*temps)
	m_py += m_vy * dt;
	m_px += m_vx * dt;

	//debug
	//std::cout << m_px << "  " << m_py << std::endl;
	//std::cout << m_vx << "  " << m_vy << std::endl;
	//std::cout << dt << std::endl;

	//vérification des collisions avec les bords de la carte
	if (m_px > xborder - 48.0) { m_px = float(xborder - 48); m_vx = 0.0; std::cout << "hors limite x max "; };
	if (m_px < 0) { std::cout << m_px << "  " << m_py << std::endl; m_px = 0; m_vx = 0; std::cout << "hors limite x min ";};
	if (m_py > yborder - 48.0) { m_py = float(yborder - 48); m_vy = 0.0; std::cout << "hors limite y max ";};
	if (m_py < 0) { m_py = 0; m_vy = 0; std::cout << "hors limite y min ";};

	setPosition(getPos());

	//animation (AnimatedSprite::animate)
	animate(m_vx, m_vy, dt);
}

sf::Vector2f Character::getPos() const
{
	return sf::Vector2f(m_px, m_py);
}

Character::~Character()
{
}