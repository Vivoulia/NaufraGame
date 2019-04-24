#include "Character.h"

Character::Character(float px, float py, int textRect_width, int textRect_height, int textRect_top, int textRect_left, int hitbox_x, int hitbox_y, int hitbox_largeur, int hitbox_hauteur, std::string texture) :
	Entite (px, py, textRect_width,  textRect_height,  textRect_top,  textRect_left, hitbox_x,  hitbox_y,  hitbox_largeur,  hitbox_hauteur, texture), m_spx(px), m_spy(py)
{
	setMode("exploration");
}
void Character::setMode(std::string mode)
{
	m_mode = mode;
	if (m_mode == "exploration")
	{
		m_vmax = 150;
		m_acc = 20;
	}
	else if (m_mode == "combat")
	{
		m_vmax = 100;
		m_acc = 50;
	}
}

std::string Character::getMode()
{
	return m_mode;
}

//met � jour la position du personnage en fonction de sa vitesse et des �v�nements clavier
void Character::update(int xborder, int yborder, float dt, std::vector<Entite*>& allEntite)
{
	m_walkInput.x = 0;
	m_walkInput.y = 0;
	if (m_state == "walk")
	{
		m_state = "none";
	}
	
	//evenements clavier marche
	if (m_state == "none")
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		{
			if (!sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				m_speed.y -= m_acc; //acceleration en -y (haut)
				orient(0); //orientation du sprite vers le haut
				m_state = "walk";
				m_walkInput.y = 1;
			}
			
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
			{
				m_speed.y += m_acc;
				orient(2);
				m_state = "walk";
				m_walkInput.y = 1;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		{
			if (!sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				m_speed.x -= m_acc;
				orient(1);
				m_state = "walk";
				m_walkInput.x = 1;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
			{
				m_speed.x += m_acc;
				orient(3);
				m_state = "walk";
				m_walkInput.x = 1;
			}
		}
	}
	//v�rification du non dépassement de la vitesse max
	if (m_speed.y < 0 && m_speed.y < -m_vmax) { m_speed.y = -m_vmax; }; 
	if (m_speed.y > 0 && m_speed.y > m_vmax) { m_speed.y = m_vmax; };
	if (m_speed.x < 0 && m_speed.x < -m_vmax) { m_speed.x = -m_vmax; };
	if (m_speed.x > 0 && m_speed.x > m_vmax) { m_speed.x = m_vmax; };

	//debug
	//std::cout << m_position.x << "  " << m_position.y << std::endl;
	//std::cout << m_speed.x << "  " << m_speed.y << std::endl;
	//std::cout << dt << std::endl;

	//vérification des collisions avec les bords de la carte
	if (m_position.x > xborder - 48.0) { m_position.x = float(xborder - 48); m_speed.x = 0.0; std::cout << "hors limite x max " << std::endl;; };
	if (m_position.x < -32) { std::cout << m_position.x << "  " << m_position.y << std::endl; m_position.x = -32; m_speed.x = 0; std::cout << "hors limite x min " << std::endl;;};
	if (m_position.y > yborder - 48.0) { m_position.y = float(yborder - 48); m_speed.y = 0.0; std::cout << "hors limite y max " << std::endl;;};
	if (m_position.y < -64) { m_position.y = -64; m_speed.y = 0; std::cout << "hors limite y min " << std::endl; };


	//mise a jour hitbox
	getHitBox()->setCoord(m_position.x, m_position.y);
	//mise a jour hurtbox
	if (m_state == "attack")
	{
		sf::Vector2f center = this->getCenter();
		this->getHurtBox()->setCoord(center.x, center.y);
		for (int iEntite(0); iEntite < allEntite.size(); iEntite++)
		{
			if (this->getHurtBox()->intersect(allEntite[iEntite]->getHitBox()))
			{
				if (m_zorder != allEntite[iEntite]->getZorder())
				{
					allEntite[iEntite]->getHitBox()->setOutlineColor(sf::Color::White);
				}
			}
		}
	}
	else
	{
		this->getHurtBox()->setBoxSize(0, 0);
	}

	//sauvegarde de la position précédente OUTDATED
	m_spx = m_position.x;
	m_spy = m_position.y;
	//std::cout << m_spy << std::endl;

	//Vérification des Hitbox
	for (int iEntite(0); iEntite < allEntite.size(); iEntite++)
	{
		if (m_zorder != allEntite[iEntite]->getZorder())
		{
			//Gestion de la transparence
			if (m_zorder < allEntite[iEntite]->getZorder())
			{
				allEntite[iEntite]->setColor(sf::Color(255, 255, 255));
				if (this->getGlobalBounds().intersects(allEntite[iEntite]->getGlobalBounds()))
				{
					allEntite[iEntite]->setColor(sf::Color(255, 255, 255, 150));
				}
			}
			m_correct = sf::Vector2f(0, 0); //vecteur de correction s'il y a collision
			if (this->getHitBox()->getGlobalBounds().intersects(allEntite[iEntite]->getHitBox()->getGlobalBounds()))
			{
				std::cout << "Collision" << std::endl;
				m_correct = makeVector(this->getHitBox()->getCenter(), allEntite[iEntite]->getHitBox()->getCenter());
				m_correct = unify(makeVector(this->getHitBox()->getCenter(), allEntite[iEntite]->getHitBox()->getCenter()));
				m_position.x += (m_correct.x + (m_correct.x * std::abs(m_speed.x))) * dt;
				m_position.y += (m_correct.y + (m_correct.y * std::abs(m_speed.y))) * dt;
			}
		}
	}

	applySpeed(dt);

	//deplacement du sprite
	setPosition(getPos());
	//animation (AnimatedSprite::animate)
	animate(m_speed, dt);
	//ralentissement auto (frottements)
	if (std::abs(m_speed.x) < 10) { m_speed.x = 0; }
	if (std::abs(m_speed.y) < 10) { m_speed.y = 0; }
	if (m_walkInput.x == 0) { m_speed.x *= float(0.92); }
	if (m_walkInput.y == 0) { m_speed.y *= float(0.92); }
	//std::cout << m_state << std::endl;
}

void Character::attack(sf::Vector2f vect)
{
	if (m_state == "walk")
	{
		m_speed.x *= 0.9;
		m_speed.y *= 0.8;
	}
	if (m_state != "attack")
	{
		m_state = "attack";
		m_speed.x += vect.x * 200;
		m_speed.y += vect.y * 200;
		std::cout << m_state << "  " << vect.x << " " << vect.y << std::endl;
		//hitbox de l'attaque
		getHurtBox()->setPr(vect.x * 40, vect.y * 40);
		getHurtBox()->setSize(sf::Vector2f(40, 40));
		getHurtBox()->setBoxSize(40, 40);
	}
}

sf::Vector2f Character::getPos() const
{
	return m_position;
}

Character::~Character()
{

}