#include "ElementGraphique.h"

void ElementGraphique::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// on applique la transformation
	states.transform *= getTransform();

	// on applique la texture du tileset
	states.texture = m_texture;

	// et on dessine enfin le tableau de vertex
	target.draw(m_quad, states);
}

