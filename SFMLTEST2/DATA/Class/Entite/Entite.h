#pragma once
#include "../AnimatedSprite.h"
#include "../Hitbox.h"

class Entite : public AnimatedSprite
{
	public:
		Entite(float px, float py, int textRect_width, int textRect_height, int textRect_top, int textRect_left, int hitbox_x, int hitbox_y, int hitbox_largeur, int hitbox_hauteur, std::string texture);
		~Entite();
		virtual void update(float dt, sf::Vector2f posJoueur);
		Hitbox* getHitBox() const;
		Hitbox* getHurtBox() const;
		float getMaxHealth() const;
		float getHealth() const;
		void setMaxHealth(int maxHealth);
		void setHealth(int health);
		sf::Vector2f getPos() const;
		void setZorder(int zorder);
		int getZorder() const;
	protected:
		sf::Texture m_texture;
		float m_px;
		float m_py;
		int m_zorder;
		float m_maxHealth;
		float m_health;
		Hitbox* hitbox;
		Hitbox* hurtbox; //hurtbox de l'objet ou lors de l'attaque d'un perso
		sf::Text info;

};