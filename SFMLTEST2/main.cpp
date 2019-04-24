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
#include "DATA/Class/Entite/Foes/Papy.h"
#include "DATA/Class/Entite/Foes/Sbire.h"

int main()
{	
	bool mode_dev(true);
	//police d'écriture
	sf::Font font;
	if (!font.loadFromFile("dpcomic.ttf"))
	{
		std::cout << "police introuvable" << std::endl;
	}

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

	std::vector<ElementGraphique*> allTile = carte.getTabTuile();
	std::vector<Entite*> allEntite = carte.getTabEntite();
	sf::Clock clock; 
	
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

	sf::Text t_posx("x = "+ std::to_string( carte.getCurrentCharac()->getCenter().x), font, 25);
	t_posx.setFillColor(sf::Color::Black);
	t_posx.setPosition(600, 2);
	sf::Text t_posy("y = " + std::to_string(carte.getCurrentCharac()->getCenter().y),font,25);
	t_posy.setFillColor(sf::Color::Black);
	t_posy.setPosition(600, 25);
	sf::Text t_dt("dt : ", font, 25);
	t_dt.setFillColor(sf::Color::Black);
	t_dt.setPosition(600, 48);
	sf::Text t_mode("mode exploration", font, 30);
	t_mode.setFillColor(sf::Color::Blue);
	t_mode.setPosition(5, 0);

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
				if (carte.getCurrentCharac()->getMode() == "combat")
				{
					carte.getCurrentCharac()->attack(vect_base);
				}
			}
			if (event.type == sf::Event::EventType::KeyPressed)
			{
				//gestion du changement de mode de jeu (combat, exploration) Hotkey : M
				if (event.key.code == sf::Keyboard::M)
				{
					if (carte.getCurrentCharac()->getMode() == "combat")
					{
						std::cout << "mode exploration" << std::endl;
						carte.getCurrentCharac()->setMode("exploration");
						t_mode.setString("mode exploration");
						t_mode.setFillColor(sf::Color::Blue);
						camera.zoom(1.33333333333333333f);
					}
					else if (carte.getCurrentCharac()->getMode() == "exploration")
					{
						std::cout << "mode combat" << std::endl;
						carte.getCurrentCharac()->setMode("combat");
						t_mode.setString("mode combat");
						t_mode.setFillColor(sf::Color::Red);
						camera.zoom(0.75f);
					}
				}
				//afficher position. Hotkey : P
				else if (event.key.code == sf::Keyboard::P)
				{
					std::cout << "x =" << carte.getCurrentCharac()->getCenter().x << "y = " << carte.getCurrentCharac()->getCenter().y << std::endl;
					std::cout << "x =" << carte.getCurrentCharac()->getPos().x << "y = " << carte.getCurrentCharac()->getPos().y << std::endl;
				}
				//reset hitboxes. Hotkey : R
				else if (event.key.code == sf::Keyboard::R)
				{
					for (int i(0); i < allEntite.size(); i++)
					{
						allEntite[i]->getHitBox()->setOutlineColor(sf::Color::Black);
					}
				}
				//faire des dégats au joueur (temporaire)
				else if (event.key.code == sf::Keyboard::G)
				{
					if (mode_dev) carte.getCurrentCharac()->setHealth(carte.getCurrentCharac()->getHealth() - 10);
				}
				//soigner le joueur (temporaire)
				else if (event.key.code == sf::Keyboard::H)
				{
					if (mode_dev) carte.getCurrentCharac()->setHealth(carte.getCurrentCharac()->getHealth() + 10);
				}
				else if (event.key.code == sf::Keyboard::F3)
				{
					if (mode_dev) 
					{ mode_dev = false; }
					else 
					{ mode_dev = true; 
					std::cout << "mode dev activé" << std::endl;
					}

				}
			}
		}
		//std::cout << "Temps depuis la derniere frame:" << clock.getElapsedTime().asSeconds() << std::endl;

		allEntite = carte.getTabEntite();
		sf::Time elapsed = clock.restart();
		float dt = elapsed.asSeconds();
		//mise à jour du personnage principal
		carte.getCurrentCharac()->update(xborder, yborder, dt, allEntite); 
		carte.addEntiteMoved(carte.getCurrentCharac()); //Pb pas général (Code Vivien)
		carte.update();
		//mise à jour de la vue
		center = carte.getCurrentCharac()->getCenter();
		if (carte.getCurrentCharac()->getMode() == "exploration")
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
		window.clear(sf::Color::White);

	//AFFICHAGE
		for (int i(0); i < allTile.size(); i++)
		{	
			//affichage des tuiles
			window.draw(*allTile[i]);
		}
		sf::CircleShape circle(30);
		circle.setPosition(0, 0);
		circle.setOutlineColor(sf::Color::Red);
		circle.setOutlineThickness(1);
		circle.setPosition(00, 00);
		window.draw(circle);
		for (int i(0); i < allEntite.size(); i++)
		{
			//Affichage des entités
			window.draw(*allEntite[i]);
			if (mode_dev)
			{
				//affichage des hitboxes/hurtboxes
				window.draw(*allEntite[i]->getHitBox());
				window.draw(*allEntite[i]->getHurtBox());
			}
			//mise à jour des entités
			allEntite[i]->update(dt, carte.getCurrentCharac()->getHitBox()->getCenter());
		} 

		//HUD//
		window.setView(GUI);
		window.draw(t_mode);
		if (mode_dev) //affichage des infos de débug
		{
			//texte info
			t_posx.setString("x = " + std::to_string(carte.getCurrentCharac()->getHitBox()->getCenter().x));
			window.draw(t_posx);
			t_posy.setString("y = " + std::to_string(carte.getCurrentCharac()->getHitBox()->getCenter().y));
			window.draw(t_posy);
			t_dt.setString("dt : " + std::to_string(dt));
			window.draw(t_dt);
		}
		if (carte.getCurrentCharac()->getMode() == "exploration")
		{
			//affichage minimap
			window.setView(minimap);
			for (int i(0); i < allTile.size(); i++)
			{
				window.draw(*allTile[i]);
			}
			for (int i(0); i < allEntite.size(); i++)
			{
				//Affichage des entités
				window.draw(*allEntite[i]);
			}
		}
		else
		{
			lifeBar_red.setSize(sf::Vector2f(200*(carte.getCurrentCharac()->getHealth() / carte.getCurrentCharac()->getMaxHealth()), 25));
			if (lifeBar_red.getSize().x <= 0)
			{
				lifeBar_red.setSize(sf::Vector2f(0, 25));
				std::cout << "Le joueur est MORT. Dommage il a rien pu faire" << std::endl;
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