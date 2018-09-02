#include "TIleMap.h"


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


std::vector<std::string> split(const std::string& str, const std::string& delim)
{
	std::vector<std::string> tokens;
	size_t prev = 0, pos = 0;
	do
	{
		pos = str.find(delim, prev);
		if (pos == std::string::npos) pos = str.length();
		std::string token = str.substr(prev, pos - prev);
		if (!token.empty()) tokens.push_back(token);
		prev = pos + delim.length();
	} while (pos < str.length() && prev < str.length());
	return tokens;
}

bool TileMap::load(std::string fichier)
{
	std::vector<int> tableauTuile = loadTileMapFile(fichier); //On charge le fichier txt de la tilemap et on initialise tous les params nécessaires
	loadEntiteFile();  //On charge le fichier txt des entités et on initialise tous les params nécessaires

	//On charge la texture
	if (!m_tileset.loadFromFile(m_tilesetFile))
		return false;
	int id(0);
	for (int i(0); i < m_largeur; i++)
	{
		for (int j(0); j < m_hauteur; j++)
		{
			//Numéro de la uile
			int numeroTuile = tableauTuile[i + j * m_largeur]; //La case (i,j) devient i+j*largeur dans un tabmeau 2d
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
return true;
}

std::vector<ElementGraphique*> TileMap::getTabTuile() const
{
	return m_pTabTuile;
}

std::vector<Entite*> TileMap::getTabEntite() const
{
	return m_pTabEntite;
}

Character* TileMap::getCurrentCharac() const
{
	return m_currentCharac;
}

void TileMap::addEntiteMoved(Entite* entite)
{
	m_pTabEntiteMoved.push_back(entite);
}

void TileMap::update()
/*Trie par z-order toutes les entités qui ont bougés a partir du tableau m_pTabEntiteMoved, et du tableau m_pTabEntite contenant toutes les entités triés a l'instant t-dt*/
{
	for (int i(0); i < m_pTabEntiteMoved.size(); i++)
	{
		bool trie(false);
		Entite* currentEntite(m_pTabEntiteMoved[i]);
		int zorder(currentEntite->getZorder());
		while (!trie)
		{		
			if (zorder+1 < m_pTabEntite.size() && currentEntite->getPosition().y > m_pTabEntite[zorder + 1]->getPosition().y)
			{

				Entite* entite1 = m_pTabEntite[zorder];
				Entite* entite2 = m_pTabEntite[zorder+1];
				m_pTabEntite[zorder]->setZorder(zorder + 1);
				m_pTabEntite[zorder + 1]->setZorder(zorder);
				m_pTabEntite[zorder] = entite2;
				m_pTabEntite[zorder + 1] = entite1;
				std::cout << "ON AUGMENTE LE ZORDER" << std::endl;
			}
			else if (zorder > 0 && currentEntite->getPosition().y < m_pTabEntite[zorder - 1]->getPosition().y)
			{
				Entite* entite1 = m_pTabEntite[zorder];
				Entite* entite2 = m_pTabEntite[zorder - 1];
				m_pTabEntite[zorder]->setZorder(zorder - 1);
				m_pTabEntite[zorder - 1]->setZorder(zorder);
				m_pTabEntite[zorder] = entite2;
				m_pTabEntite[zorder - 1] = entite1;
				std::cout << "ON BAISSE LE ZORDER" << std::endl;
			}
			else
			{
				trie = true;
			}	
			zorder = currentEntite->getZorder();
		}
	}
}

std::vector<int> TileMap::loadTileMapFile(std::string fichier)
/*Charge le fichier txt de la tilemap et initialise le tableau des tuiles et d'autres params*/
{
	std::ifstream tilesetFile(fichier, std::ios::in);
	if (tilesetFile)
	{
		char carac; //Caractère pour la lecture du fichier caractère par caracère
		std::string numTuile(""); //Stock le numero de la tuile courante 
		std::string ligne; //Ligne pour la lecture ligne par ligne
		std::vector<int> tableauTuile; //Tableau contenant tous les numero des tuiles
		//On recupère les premières lignes qui sont des paramètres
		std::getline(tilesetFile, ligne);
		m_tilesetFile = ligne;
		std::getline(tilesetFile, ligne);
		m_entiteFileName = ligne;
		std::getline(tilesetFile, ligne);
		m_tileSize = sf::Vector2u(std::stoi(ligne), std::stoi(ligne));
		std::getline(tilesetFile, ligne);
		m_largeur = std::stoi(ligne);
		std::getline(tilesetFile, ligne);
		m_hauteur = std::stoi(ligne);
		//On parcours le fichier caractère par caractère pour recuperer chaque numero de tuile
		while (tilesetFile.get(carac))
		{
			if (to_int(carac) != -1)
			{
				//On lit tant qu'il y a des nombres au cas ou il a plusieurs chiffres
				numTuile += std::to_string(to_int(carac));
			}
			else if (carac == ',' || carac == ';')
			{
				tableauTuile.push_back(std::stoi(numTuile));
				numTuile = "";
			}
		}
		tilesetFile.close();

		return tableauTuile;
	}
	else
	{
		std::cout << "Impossible d'ouvrir le fichier de tileset" << std::endl;
	}

}

void TileMap::loadEntiteFile()
/*Charge le fichier txt des entités et initialise m_pTabEntite tableau contenant des pointeurs vers toutes les entités trié par z-order croissant*/
{
	std::ifstream entiteFile(m_entiteFileName, std::ios::in);
	if (entiteFile)
	{
		std::string ligne; //Ligne pour la lecture ligne par ligne
		m_currentCharac = new Baba(20,20);
		m_currentCharac->setZorder(0);
		m_pTabEntite.push_back(m_currentCharac);
		int iData(0);
		int jEntite(1); //On commence a 1 car 0 est utilisé pour le perso (pour l'instant)

		int x(0);
		int y(0);
		int zorder(0);
		std::string className("");

		while (std::getline(entiteFile, ligne))
		{
			if (iData == 0)
			{
				std::cout << ligne << std::endl;
				className = ligne;
				iData++;
			}
			else if (iData == 1)
			{
				std::cout << ligne << std::endl;
				x = std::stoi(ligne);
				iData++;
			}
			else if (iData == 2)
			{
				std::cout << ligne << std::endl;
				y = std::stoi(ligne);
				m_pTabEntite.push_back(EntiteFactory::createEntite(x, y, className));
				iData++;
			}
			else if (iData == 3)
			{
				std::cout << ligne << std::endl;
				zorder = std::stoi(ligne);
				iData = 0;
				m_pTabEntite[jEntite]->setZorder(zorder);
				jEntite++;
			}


		}
	}
	else
	{
		std::cout << "Impossible d'ouvrir le fichier des entites" << std::endl;
	}
}

TileMap::~TileMap()
{
	for (int i(0); i < m_pTabTuile.size(); i++)
	{
		//On detruit tous les pointeurs fait en allocation dynamique
		delete m_pTabTuile[i];
	}
	for (int i(0); i < m_pTabEntite.size(); i++)
	{
		//On detruit tous les pointeurs fait en allocation dynamique
		delete m_pTabEntite[i];
	}

}

