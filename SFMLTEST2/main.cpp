#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "DATA/Class/Terrain/TileMap.h"
#include "DATA/Class/Terrain/ElementGraphique.h"
#include "DATA/Class/Entite/Character/Baba.h"
#include "DATA/Class/Hitbox.h"
#include "DATA/Class/Entite/Decors/Maison.h"
#include "DATA/Class/Entite/Decors/Arbre.h"
#include "DATA/Class/Entite/Decors/Echoppe.h"
#include "DATA/Class/Entite/Decors/Papy.h"
#include "DATA/Class/Entite/Decors/Sbire.h"

int main()
{	
	//police d'écriture
	sf::Font font;
	if (!font.loadFromFile("dpcomic.ttf"))
	{
		// erreur...
	}
	//elements du HUD
	sf::Sprite lifeBar;
	sf::Texture lifeBar_texture;
	if (!lifeBar_texture.loadFromFile("DATA/Ressources/Textures/lifeBar.png"))
	{
		std::cout << "mdr ya pas la texture" << std::endl;
	}
	lifeBar.setTexture(lifeBar_texture);
	lifeBar.setTextureRect(sf::IntRect(0, 0, 142, 44));
	lifeBar.setPosition(10, 30);
	lifeBar.setScale(2, 2);
	//barre de vie
	sf::RectangleShape lifeBar_red;
	lifeBar_red.setSize(sf::Vector2f(200, 25));
	lifeBar_red.setPosition((lifeBar.getPosition().x + 82), lifeBar.getPosition().y + 18);
	lifeBar_red.setFillColor(sf::Color::Red);
	//halo jaune de la barre de vie quand on prend un coup
	sf::RectangleShape lifeBar_subRed;
	lifeBar_subRed.setSize(sf::Vector2f(200, 25));
	lifeBar_subRed.setPosition((lifeBar.getPosition().x + 82), lifeBar.getPosition().y + 18);
	lifeBar_subRed.setFillColor(sf::Color::Yellow);
	//barre de "mana"
	sf::RectangleShape lifeBar_blue;
	lifeBar_blue.setSize(sf::Vector2f(178, 25));
	lifeBar_blue.setPosition((lifeBar.getPosition().x + 82), lifeBar.getPosition().y + 47);
	lifeBar_blue.setFillColor(sf::Color::Blue);

	sf::Text posx("x = ", font, 25);
	posx.setFillColor(sf::Color::Black);
	posx.setPosition(650, 2);
	sf::Text posy("y = ",font,25);
	posy.setFillColor(sf::Color::Black);
	posy.setPosition(650, 25);
	sf::Text MODE("mode exploration", font, 30);
	MODE.setFillColor(sf::Color::Blue);
	MODE.setPosition(5, 0);

	//paramètrage de la fenêtre
	int resoX(800);
	int resoY(600);
	sf::RenderWindow window(sf::VideoMode(resoX, resoY), "NaufraGame tests SFML");

	sf::Vector2i mousePos; //tracking de la souris
	sf::Vector2f vect; //vecteur entre le joueur et la souris
	sf::Vector2f vect_base; //direction du vecteur rapportée à 1
	sf::Vector2i cameraDirection; //direction du centre de la caméra de rencetrage

	//réglage des vues
	sf::View camera;
	camera.setViewport(sf::FloatRect(0, 0, 1, 1));
	camera.setSize(sf::Vector2f(resoX, resoY));
	camera.zoom(0.8f);
	sf::View GUI;
	GUI = window.getView();
	sf::View minimap;
	minimap.setViewport(sf::FloatRect(0.70f, 0.10f, 0.25f, 0.25f));
	minimap.zoom(1.7f);
	
	sf::Vector2f center; //centre de l'écran
	int xborder(1500); //limites de la map (temporaire
	int yborder(1500);

	TileMap carte;
	if (!carte.load("tileset0_doc.txt"))
		return -1;

	std::vector<ElementGraphique*> pileAffichageTileMap = carte.getTabTuile();
	std::vector<Entite*> pileAffichageEntite = carte.getTabEntite();

	Baba player1(450, 450);
	Papy papy(310, 120);
	Sbire sbire(200, 200);
	Maison maison(180, -73);
	Arbre arbre(100, 630);
	Echoppe echoppe(590, 75);

	sf::Clock clock; 
	
	while (window.isOpen())
	{
		window.setView(camera);
		sf::Event event;
		//mise à jour des positions de souris et vecteurs associés
		mousePos = sf::Mouse::getPosition(window);
		vect = sf::Vector2f(mousePos.x - float(window.getSize().x / 2), mousePos.y - float(window.getSize().y / 2));
		//création du vecteur unitaire
		if (std::abs(vect.x) > std::abs(vect.y))
		{ 
			vect_base.y = std::abs(vect.y / vect.x);
			if (vect.y < 0) { vect_base.y *= -1; }
			if (vect.x < 0) { vect_base.x = -1;}
			else {vect_base.x = 1;}
		}
		else
		{
			vect_base.x = std::abs(vect.x / vect.y);
			if (vect.x < 0) { vect_base.x *= -1; }
			if (vect.y < 0) { vect_base.y = -1; }
			else { vect_base.y = 1; }
		}
		 
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (player1.getMode() == "combat")
				{
					player1.attack(vect_base);
				}
			}
			if (event.type == sf::Event::EventType::KeyPressed)
			{
				//gestion du changement de mode de jeu (combat, exploration) Hotkey : M
				if (event.key.code == sf::Keyboard::M)
				{
					if (player1.getMode() == "combat")
					{
						std::cout << "mode exploration" << std::endl;
						player1.setMode("exploration");
						MODE.setString("mode exploration");
						MODE.setFillColor(sf::Color::Blue);
						camera.zoom(1.33333333333333333f);
					}
					else if (player1.getMode() == "exploration")
					{
						std::cout << "mode combat" << std::endl;
						player1.setMode("combat");
						MODE.setString("mode combat");
						MODE.setFillColor(sf::Color::Red);
						camera.zoom(0.75f);
					}
				}
				//afficher position. Hotkey : P
				else if (event.key.code == sf::Keyboard::P)
				{
					std::cout << "x =" << player1.getPos().x << "y = " << player1.getPos().y << std::endl;
				}
				//reset hitboxes. Hotkey : R
				else if (event.key.code == sf::Keyboard::R)
				{
					maison.getHitBox()->setOutlineColor(sf::Color::Black);
					arbre.getHitBox()->setOutlineColor(sf::Color::Black);
					echoppe.getHitBox()->setOutlineColor(sf::Color::Black);
				}
				//faire des dégats au joueur (temporaire)
				else if (event.key.code == sf::Keyboard::G)
				{
					player1.setHealth(player1.getHealth() - 10);
				}
				//soigner le joueur (temporaire)
				else if (event.key.code == sf::Keyboard::H)
				{
					player1.setHealth(player1.getHealth() + 10);
				}
			}
		}
		//std::cout << "Temps depuis la derniere frame:" << clock.getElapsedTime().asSeconds() << std::endl;

		pileAffichageEntite = carte.getTabEntite();
		sf::Time elapsed = clock.restart();
		float dt = elapsed.asSeconds();
		//mise à jour du personnage principal
		player1.update(xborder, yborder, dt, maison.getHitBox(), arbre.getHitBox(), echoppe.getHitBox());
		//mise à jour des entités
		papy.update(dt, player1.getCenter());
		sbire.update(dt, player1.getCenter());
		//mise à jour de la vue
		center = player1.getCenter();
		if (player1.getMode() == "exploration")
		{
			cameraDirection = sf::Vector2i(center.x + vect.x / 3 - camera.getCenter().x, center.y + vect.y / 3 - camera.getCenter().y);

			camera.setCenter(sf::Vector2f(camera.getCenter().x + (cameraDirection.x*0.02), 0.05 + camera.getCenter().y + (cameraDirection.y*0.05)));
			//view.setCenter(sf::Vector2f(center.x + vect.x/4, center.y + vect.y/4));
			minimap.setCenter(center);
		}
		else
		{
			camera.setCenter(center);
		}
		center = carte.getCurrentCharac()->getPos();
		view.setCenter(center);
		window.clear(sf::Color::White);

		//affichage de la tilemap
		for (int i(0); i < pileAffichageTileMap.size(); i++)
		{
			window.draw(*pileAffichageTileMap[i]);
		}
		for (int i(0); i < pileAffichageEntite.size(); i++)
		{
			window.draw(*pileAffichageEntite[i]);
		} 

		carte.getCurrentCharac()->update(xborder, yborder, dt);
		carte.addEntiteMoved(carte.getCurrentCharac());
		carte.update();
		//affichage des sprite (z order temporaire)

		window.draw(maison);
		window.draw(arbre);
		window.draw(echoppe);
		window.draw(papy);
		window.draw(sbire);
		window.draw(player1);

		//affichage des hitboxes
		window.draw(*maison.getHitBox());
		window.draw(*arbre.getHitBox());
		window.draw(*player1.getHitBox());
		window.draw(*echoppe.getHitBox());
		window.draw(*papy.getHitBox());
		window.draw(*player1.getHurtBox());
		window.draw(*sbire.getHitBox());

		//HUD//
		window.setView(GUI);
		window.draw(MODE);
		if (player1.getMode() == "exploration")
		{
			//texte
			window.draw(posx);
			window.draw(posy);
			//affichage minimap
			window.setView(minimap);
			for (int i(0); i < pileAffichageTileMap.size(); i++)
			{
				window.draw(*pileAffichageTileMap[i]);
			}
			window.draw(maison);
			window.draw(arbre);
			window.draw(echoppe);
			window.draw(player1);
		}
		else
		{
			lifeBar_red.setSize(sf::Vector2f(200*(player1.getHealth() / player1.getMaxHealth()), 25));
			if (lifeBar_red.getSize().x <= 0)
			{
				lifeBar_red.setSize(sf::Vector2f(0, 25));
				std::cout << "Le joueur est décédé. Dommage il a rien pu faire" << std::endl;
			}
			if (lifeBar_red.getSize().x < lifeBar_subRed.getSize().x)
			{
				lifeBar_subRed.setSize((sf::Vector2f(lifeBar_subRed.getSize().x - (0.01*(lifeBar_subRed.getSize().x - lifeBar_red.getSize().x)) - 0.1, 25)));
			}
			if (lifeBar_red.getSize().x > lifeBar_subRed.getSize().x)
			{
				lifeBar_subRed.setSize((sf::Vector2f(lifeBar_red.getSize().x, 25)));
			}
			window.draw(lifeBar_subRed);
			window.draw(lifeBar_red);
			window.draw(lifeBar_blue);
			window.draw(lifeBar);

		}
		window.display();
	}

	return 0;
}