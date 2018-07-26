#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	sf::Clock clock; 
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
		window.display();
	}

	return 0;
}