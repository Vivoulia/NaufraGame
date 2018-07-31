#include <SFML/Graphics.hpp>
#include <iostream>
#include "TIleMap.h"
#include "ElementGraphique.h"
#include "Character.h"

int main()
{
	sf::Texture* textureBaba(0);
	sf::Sprite spriteBaba;
	sf::View view;
	view.setSize(sf::Vector2f(800, 600));
	sf::Vector2f center;
	int xborder(1500);
	int yborder(1500);

	TileMap carte;
	if (!carte.load("test.txt"))
		return -1;

	std::vector<ElementGraphique*> pileAffichageTileMap = carte.getTabTuile();

	Character baba("walk.png");

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
		window.display();
	}

	return 0;
}