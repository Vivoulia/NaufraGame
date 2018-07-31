#pragma once
#include "SFML/Graphics.hpp"
class ElementGraphique : public sf::Drawable, public sf::Transformable
{
public:
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::Texture* m_texture;
	sf::VertexArray m_quad;
};