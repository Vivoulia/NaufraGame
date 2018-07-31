#pragma once
#include <SFML/Graphics.hpp>
#include "ElementGraphique.h"


class Tuile : public ElementGraphique
{
public:
	Tuile(sf::VertexArray quad, sf::Texture* texture, int id);
	~Tuile();
	sf::Texture* getTexture() const;
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::VertexArray m_quad; 
	sf::Texture* m_texture; //Pointeur vers la texture de la tilesheet 
	int m_id;
};