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
		sf::Vector2f getCenter();
		void setCenter(float px, float py);
		void applyVector(sf::Vector2f vector);
		void applySpeed(float dt);
		sf::Vector2f unify(sf::Vector2f vect);
		sf::Vector2f multiply(sf::Vector2f vector, float facteur);
		sf::Vector2f makeVector(sf::Vector2f vector1, sf::Vector2f vector2);
	protected:
		sf::Texture m_texture;
		sf::Vector2f m_speed;
		sf::Vector2f m_correct; //vecteur de collision
		sf::Vector2f m_position;
		sf::Vector2f m_center;
		int m_zorder;
		float m_maxHealth;
		float m_health;
		Hitbox* hitbox;
		Hitbox* hurtbox; //hurtbox de l'objet ou lors de l'attaque d'un perso
		sf::Text info;

};