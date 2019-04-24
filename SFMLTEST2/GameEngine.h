#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include <string>
#include "DATA/Class/Terrain/TileMap.h"
#include "DATA/Class/Terrain/ElementGraphique.h"
#include "DATA/Class/Entite/Character/Baba.h"
#include "DATA/Class/Hitbox.h"
#include "DATA/Class/Entite/Decors/Maison.h"
#include "DATA/Class/Entite/Decors/Arbre.h"
#include "DATA/Class/Entite/Decors/Echoppe.h"
#include "DATA/Class/Entite/Foes/Papy.h"
#include "DATA/Class/Entite/Foes/Sbire.h"

class GameEngine
{
public:

	GameEngine();
	~GameEngine();

protected :
	sf::Font font; //police d'écriture
	sf::Vector2i mousePos; //tracking de la souris
	sf::Vector2f vect; //vecteur entre le joueur et la souris
	sf::Vector2f vect_base; //direction du vecteur rapportée à 1
	sf::Vector2i cameraDirection; //direction du centre de la caméra de rencetrage
};

