#include <SFML/Graphics.hpp>
#include <iostream>
#include "DATA/Class/Terrain/TileMap.h"
#include "DATA/Class/Terrain/ElementGraphique.h"
#include "DATA/Class/Entite/Character/Baba.h"
#include "DATA/Class/Hitbox.h"
#include "DATA/Class/Entite/Decors/Maison.h"
#include "DATA/Class/Entite/Decors/Arbre.h"

int main()
{
	sf::View view;
	view.setSize(sf::Vector2f(800, 600));
	sf::Vector2f center;
	int xborder(1500);
	int yborder(1500);

	TileMap carte;
	if (!carte.load("tileset3_doc.txt"))
		return -1;

	std::vector<ElementGraphique*> pileAffichageTileMap = carte.getTabTuile();

	Baba baba;
	Maison maison;
	Arbre arbre;
	maison.setPosition(sf::Vector2f(100, 100));
	arbre.setPosition(sf::Vector2f(300, 100));

	sf::RenderWindow window(sf::VideoMode(800, 600), "NaufraGame tests SFML");
	sf::Clock clock; 
	
	while (window.isOpen())
	{
		window.setView(view);
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::EventType::KeyPressed)
			{
				//std::cout << event.key.code << std::endl;
				if (event.key.code == sf::Keyboard::Space)
				{
					std::cout << "Barre espace" << std::endl;
				}
			}
		}

		//std::cout << "Temps depuis la dernière frame:" << clock.getElapsedTime().asSeconds() << std::endl;
		sf::Time elapsed = clock.restart();
		float dt = elapsed.asSeconds();

		baba.update(xborder, yborder, dt);
		center = baba.getPos();
		view.setCenter(center);
		window.clear(sf::Color::White);
		for (int i(0); i < pileAffichageTileMap.size(); i++)
		{
			window.draw(*pileAffichageTileMap[i]);
		}
		window.draw(baba); //affichage du sprite
		/*GESTION TEMPORAIRE DE LA HITBOX*/
		baba.getHitBox()->setCoord(baba.getPosition().x, baba.getPosition().y);
		window.draw(*baba.getHitBox());
		window.draw(maison);
		window.draw(arbre);
		window.display();
	}

	return 0;
}