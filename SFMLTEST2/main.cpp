#include <SFML/Graphics.hpp>
#include <iostream>
#include "TIleMap.h"
#include "ElementGraphique.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!");

	sf::Clock clock; 
	TileMap carte;
	if (!carte.load("test.txt"))
		return -1;

	std::vector<ElementGraphique*> pileAffichageTileMap = carte.getTabTuile();

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::EventType::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Space)
				{
					std::cout << "Barre espace" << std::endl;
				}
			}
		}
		//std::cout << "Temps depuis la dernière frame:" << clock.getElapsedTime().asSeconds() << std::endl;
		clock.restart();
		window.clear();

		for (int i(0); i < pileAffichageTileMap.size(); i++)
		{
			window.draw(*pileAffichageTileMap[i]);
		}

		window.display();
	}

	return 0;
}