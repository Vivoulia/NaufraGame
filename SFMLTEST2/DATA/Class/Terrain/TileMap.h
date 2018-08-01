#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Tuile.h"

class TileMap
{
public:
	bool load(std::string fichier);
	std::vector<ElementGraphique*> getTabTuile() const;
	~TileMap();
	
protected:
	sf::Texture m_tileset;
	//Tableau element graphique contenant des pointeurs Tuiles (polymorphisme) 
	std::vector<ElementGraphique*> m_pTabTuile; 
	std::string m_tilesetFile;
	sf::Vector2u m_tileSize;
	int m_largeur;
	int m_hauteur;
};