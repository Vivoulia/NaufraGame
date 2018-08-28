#include "Character.h"

Character::Character(float px, float py, int textRect_width, int textRect_height, int textRect_top, int textRect_left, int hitbox_x, int hitbox_y, int hitbox_largeur, int hitbox_hauteur, std::string texture) : 
	Entite (px, py, textRect_width,  textRect_height,  textRect_top,  textRect_left, hitbox_x,  hitbox_y,  hitbox_largeur,  hitbox_hauteur, texture),  m_vx(0), m_vy(0), m_spx(0), m_spy(0)
{
	setMode("exploration");
}
void Character::setMode(std::string mode)
{
	m_mode = mode;
	if (m_mode == "exploration")
	{
		m_vmax = 200;
		m_acc = 10;
	}
	else if (m_mode == "combat")
	{
		m_vmax = 150;
		m_acc = 100;
	}
}

std::string Character::getMode()
{
	return m_mode;
}

//met � jour la position du personnage en fonction de sa vitesse et des �v�nements clavier
void Character::update(int xborder, int yborder, float dt, Hitbox* obstacle1, Hitbox* obstacle2, Hitbox* obstacle3)
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
				m_vy -= m_acc; //acceleration en -y (haut)
				orient(0); //orientation du sprite vers le haut
				m_state = "walk";
				m_walkInput.y = 1;
			}
			
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
			{
				m_vy += m_acc;
				orient(2);
				m_state = "walk";
				m_walkInput.y = 1;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		{
			if (!sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				m_vx -= m_acc;
				orient(1);
				m_state = "walk";
				m_walkInput.x = 1;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
			{
				m_vx += m_acc;
				orient(3);
				m_state = "walk";
				m_walkInput.x = 1;
			}
		}
	}
	//v�rification du non d�passement de la vitesse max
	if (m_vy < 0 && m_vy < -m_vmax) { m_vy = -m_vmax; }; 
	if (m_vy > 0 && m_vy > m_vmax) { m_vy = m_vmax; };
	if (m_vx < 0 && m_vx < -m_vmax) { m_vx = -m_vmax; };
	if (m_vx > 0 && m_vx > m_vmax) { m_vx = m_vmax; };

	//debug
	//std::cout << m_px << "  " << m_py << std::endl;
	//std::cout << m_vx << "  " << m_vy << std::endl;
	//std::cout << dt << std::endl;

	//v�rification des collisions avec les bords de la carte
	if (m_px > xborder - 48.0) { m_px = float(xborder - 48); m_vx = 0.0; std::cout << "hors limite x max " << std::endl;; };
	if (m_px < -32) { std::cout << m_px << "  " << m_py << std::endl; m_px = -32; m_vx = 0; std::cout << "hors limite x min " << std::endl;;};
	if (m_py > yborder - 48.0) { m_py = float(yborder - 48); m_vy = 0.0; std::cout << "hors limite y max " << std::endl;;};
	if (m_py < -64) { m_py = -64; m_vy = 0; std::cout << "hors limite y min " << std::endl; };


	//mise � jour hitbox
	getHitBox()->setCoord(m_px, m_py);
	//mise � jour hurtbox
	if (m_state == "attack")
	{
		sf::Vector2f center = getCenter();
		getHurtBox()->setCoord(center.x, center.y);
		if (getHurtBox()->intersect(obstacle1))
		{
			obstacle1->setOutlineColor(sf::Color::White);
		}
		if (getHurtBox()->intersect(obstacle2) || obstacle2->intersect(getHurtBox()))
		{
			obstacle2->setOutlineColor(sf::Color::White);
		}
		if (getHurtBox()->intersect(obstacle3)|| obstacle3->intersect(getHurtBox()))
		{
			obstacle3->setOutlineColor(sf::Color::White);
		}
	}
	else
	{
		getHurtBox()->setBoxSize(0, 0);
	}
	

	//v�rification des hitboxes (temporaire, la version finale se fera avec une boucle qui explore toutes les entit�s)
	if (getHitBox()->intersect(obstacle1))
	{
		m_vy = 0;
		m_py = m_spy;
		m_vx = 0;
		m_px = m_spx;
		/*sf::Vector2f correction(getHitBox()->detailCollision(obstacle1));
		if (correction.x != 0)
		{
			m_vx = 0;
			m_px = m_spx;
		}
		if (correction.y != 0)
		{
			m_vy = 0;
			m_py = m_spy;
		}*/
	}

	if  (getHitBox()->intersect(obstacle2))
	{
		m_vy = 0;
		m_py = m_spy;
		m_vx = 0;
		m_px = m_spx;
		/*sf::Vector2f correction(getHitBox()->detailCollision(obstacle2));
		if (correction.x != 0)
		{
			m_vx = 0;
			m_px = m_spx;
		}
		if (correction.y != 0)
		{
			m_vy = 0;
			m_py = m_spy;
		}*/
	}

	if (getHitBox()->intersect(obstacle3))
	{
		m_vy = 0;
		m_py = m_spy;
		m_vx = 0;
		m_px = m_spx;
	/*	sf::Vector2f correction(getHitBox()->detailCollision(obstacle3));
		if (correction.x != 0)
		{
			m_vx = 0;
			m_px = m_spx;
		}
		if (correction.y != 0)
		{
			m_vy = 0;
			m_py = m_spy;
		}*/
	}

	//sauvegarde de la position pr�c�dente
	m_spx = m_px;
	m_spy = m_py;
	//std::cout << m_spy << std::endl;
	//reposionnement de l'entit� (+= vitesse*temps)
	m_py += m_vy * dt;
	m_px += m_vx * dt;
	//d�placement du sprite
	setPosition(getPos());
	//animation (AnimatedSprite::animate)
	animate(m_vx, m_vy, dt);
	//ralentissement auto (frottements)
	if (m_walkInput.x == 0) {m_vx *= float(0.92);}
	if (m_walkInput.y == 0) { m_vy *= float(0.92);}
	//std::cout << m_state << std::endl;
}

void Character::attack(sf::Vector2f vect)
{

	if (m_state == "walk")
	{
		m_vx *= 0.8;
		m_vy *= 0.8;
	}
	if (m_state != "attack")
	{
		m_state = "attack";
		m_vx += vect.x * 200;
		m_vy += vect.y * 200;
		std::cout << m_state << "  " << vect.x << " " << vect.y << std::endl;
		//hitbox de l'attaque
		getHurtBox()->setPr(vect.x * 40, vect.y * 40);
		getHurtBox()->setSize(sf::Vector2f(40, 40));
		getHurtBox()->setBoxSize(40, 40);
	}
}

sf::Vector2f Character::getPos() const
{
	return sf::Vector2f(m_px, m_py);
}

sf::Vector2f Character::getCenter() const
{
	return sf::Vector2f(m_px + 32, m_py + 40);
}

Character::~Character()
{

}