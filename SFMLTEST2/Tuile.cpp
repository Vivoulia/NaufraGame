#include "Tuile.h"

Tuile::Tuile(sf::VertexArray quad, sf::Texture* texture, int id)
{
	m_quad = quad;
	m_texture = texture;
	m_id = id;
}

Tuile::~Tuile()
{
	//delete m_quad;
	//delete m_texture;
}
void Tuile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// on applique la transformation
	states.transform *= getTransform();

	// on applique la texture du tileset
	states.texture = m_texture;

	// et on dessine enfin le tableau de vertex
	target.draw(m_quad, states);
}


sf::Texture* Tuile::getTexture() const
{
	return m_texture;
}
