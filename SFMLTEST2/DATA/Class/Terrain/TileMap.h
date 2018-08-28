#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include "Tuile.h"
#include "../Entite/Entite.h"
#include "../Entite/Character/Character.h"
#include "../EntiteFactory.h"

class TileMap
{
public:
	bool load(std::string fichier);
	std::vector<ElementGraphique*> getTabTuile() const;
	std::vector<Entite*> getTabEntite() const;
	Character* getCurrentCharac() const;
	void addEntiteMoved(Entite* entite);
	void update();
	~TileMap();
	
protected:
	std::vector<int> loadTileMapFile(std::string fichier);
	void loadEntiteFile();
	sf::Texture m_tileset;
	//Tableau element graphique contenant des pointeurs Tuiles (polymorphisme) 
	std::vector<ElementGraphique*> m_pTabTuile; 
	std::vector<Entite*> m_pTabEntite;
	std::vector<Entite*> m_pTabEntiteMoved;
	Character* m_currentCharac;
	std::string m_tilesetFile;
	std::string m_entiteFileName;
	sf::Vector2u m_tileSize;
	int m_largeur;
	int m_hauteur;

};