#include "TIleMap.h"
#include <iostream>
#include <fstream>
#include <string>

int to_int(char c)
{
	switch (c)
	{   //  makes no assumptions about character order
	case '0': return 0;
	case '1': return 1;
	case '2': return 2;
	case '3': return 3;
	case '4': return 4;
	case '5': return 5;
	case '6': return 6;
	case '7': return 7;
	case '8': return 8;
	case '9': return 9;
	default: return -1;
	}
}

bool TileMap::load(std::string fichier)
{
	
	std::ifstream map(fichier, std::ios::in);
	if (map)
	{
		char carac; //Caractère pour la lecture du fichier caractère par caracère
		std::string numTuile(""); //Stock le numero de la tuile courante 
		std::string ligne; //Ligne pour la lecture ligne par ligne
		std::vector<int> tableau; //Tableau contenant tous les numero des tuiles
		//On recupère les premières lignes qui sont des paramètres
		std::getline(map, ligne);
		m_tilesetFile = ligne;
		std::getline(map, ligne);
		m_tileSize = sf::Vector2u(std::stoi(ligne), std::stoi(ligne));
		std::getline(map, ligne);
		m_largeur = std::stoi(ligne);
		std::getline(map, ligne);
		m_hauteur = std::stoi(ligne);

		//On parcours le fichier caractère par caractère pour recuperer chaque numero de tuile
		while (map.get(carac))
		{
			if (to_int(carac) != -1) 
			{	
				//On lit tant qu'il y a des nombres au cas ou il a plusieurs chiffres
				numTuile += std::to_string(to_int(carac));
				
			}
			else if (carac == ',' || carac == ';')
			{
				tableau.push_back(std::stoi(numTuile));
				numTuile = "";
			}
		}
		map.close();
		//On charge la texture
		if (!m_tileset.loadFromFile(m_tilesetFile))
			return false;
		int id(0);
		for (int i(0); i < m_largeur; i++)
		{
			for (int j(0); j < m_hauteur; j++)
			{
				//Numéro de la uile
				int numeroTuile = tableau[i + j * m_largeur]; //La case (i,j) devient i+j*largeur dans un tabmeau 2d
				//Position dans le tileset
				int tu = numeroTuile % (m_tileset.getSize().x / m_tileSize.x);
				int tv = numeroTuile / (m_tileset.getSize().x / m_tileSize.x);
				//Quad qui pointe vers le tableau de vertex
				sf::VertexArray quad(sf::Quads, 4);
				quad[0].position = sf::Vector2f(i * m_tileSize.x, j * m_tileSize.y);
				quad[1].position = sf::Vector2f((i + 1) * m_tileSize.x, j * m_tileSize.y);
				quad[2].position = sf::Vector2f((i + 1) * m_tileSize.x, (j + 1) * m_tileSize.y);
				quad[3].position = sf::Vector2f(i * m_tileSize.x, (j + 1) * m_tileSize.y);
				// on définit ses quatre coordonnées de texture
				quad[0].texCoords = sf::Vector2f(tu * m_tileSize.x, tv * m_tileSize.y);
				quad[1].texCoords = sf::Vector2f((tu + 1) * m_tileSize.x, tv * m_tileSize.y);
				quad[2].texCoords = sf::Vector2f((tu + 1) * m_tileSize.x, (tv + 1) * m_tileSize.y);
				quad[3].texCoords = sf::Vector2f(tu * m_tileSize.x, (tv + 1) * m_tileSize.y);

				//Allocation dynamique d'une Tuile dans le tableau de type ElementGraphique
				m_pTabTuile.push_back(new Tuile(quad, &m_tileset, id));
				id++;
			}
		}
	}
	else
	{
		std::cout << "Impossible d'ouvrir le fichier" << std::endl;
	}

	return true;
}

std::vector<ElementGraphique*> TileMap::getTabTuile() const
{
	return m_pTabTuile;
}

TileMap::~TileMap()
{
	for (int i(0); i < m_pTabTuile.size(); i++)
	{
		//On detruit tous les pointeurs fait en allocation dynamique
		delete m_pTabTuile[i];
	}
}

