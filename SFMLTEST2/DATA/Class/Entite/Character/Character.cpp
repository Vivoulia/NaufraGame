#include "Character.h"

Character::Character(float px, float py, int textRect_width, int textRect_height, int textRect_top, int textRect_left, int hitbox_x, int hitbox_y, int hitbox_largeur, int hitbox_hauteur, std::string texture) :
	Entite (px, py, textRect_width,  textRect_height,  textRect_top,  textRect_left, hitbox_x,  hitbox_y,  hitbox_largeur,  hitbox_hauteur, texture),  m_vx(0), m_vy(0), m_spx(px), m_spy(py)
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
	//v�rification du non dépassement de la vitesse max
	if (m_vy < 0 && m_vy < -m_vmax) { m_vy = -m_vmax; }; 
	if (m_vy > 0 && m_vy > m_vmax) { m_vy = m_vmax; };
	if (m_vx < 0 && m_vx < -m_vmax) { m_vx = -m_vmax; };
	if (m_vx > 0 && m_vx > m_vmax) { m_vx = m_vmax; };

	//debug
	//std::cout << m_px << "  " << m_py << std::endl;
	//std::cout << m_vx << "  " << m_vy << std::endl;
	//std::cout << dt << std::endl;

	//vérification des collisions avec les bords de la carte
	if (m_px > xborder - 48.0) { m_px = float(xborder - 48); m_vx = 0.0; std::cout << "hors limite x max " << std::endl;; };
	if (m_px < -32) { std::cout << m_px << "  " << m_py << std::endl; m_px = -32; m_vx = 0; std::cout << "hors limite x min " << std::endl;;};
	if (m_py > yborder - 48.0) { m_py = float(yborder - 48); m_vy = 0.0; std::cout << "hors limite y max " << std::endl;;};
	if (m_py < -64) { m_py = -64; m_vy = 0; std::cout << "hors limite y min " << std::endl; };


	//mise a jour hitbox
	getHitBox()->setCoord(m_px, m_py);
	//mise a jour hurtbox
	if (m_state == "attack")
	{
		sf::Vector2f center = this->getCenter();
		this->getHurtBox()->setCoord(center.x, center.y);
		for (int iEntite(0); iEntite < allEntite.size(); iEntite++)
		{
			if (this->getHurtBox()->intersect(allEntite[iEntite]->getHitBox()) || allEntite[iEntite]->getHitBox()->intersect(this->getHurtBox()))
			{
				allEntite[iEntite]->getHurtBox()->setOutlineColor(sf::Color::White);
			}
		}
	}
	else
	{
		this->getHurtBox()->setBoxSize(0, 0);
	}
	
	//Vérification des Hitbox
	for (int iEntite(0); iEntite < allEntite.size(); iEntite++)
	{
		if (m_zorder != allEntite[iEntite]->getZorder())
		{
			if (this->getHitBox()->intersect(allEntite[iEntite]->getHitBox()))
			{
				std::cout << "Collision" << std::endl;
				m_vy = 0;
				m_py = m_spy;
				m_vx = 0;
				m_px = m_spx;
			}
		}

	}

	//sauvegarde de la position précédente
	m_spx = m_px;
	m_spy = m_py;
	//std::cout << m_spy << std::endl;
	//reposionnement de l'entité (+= vitesse*temps)
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