#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>
#include <chrono>
#include "Desk.h"

class SfmlControlManager {
	sf::RenderWindow window;
	sf::Texture desk_texture;
	sf::Texture figure_textures;
	sf::Sprite desk_sprite;
	std::vector<sf::Sprite> figure_sprites;

	std::shared_ptr<Desk> desk;

public:
	SfmlControlManager() {
		desk = make_shared<Desk>();
		desk->PlaceDefaultFigures();


		window.create(sf::VideoMode(640, 640), "Chess");
		if (!desk_texture.loadFromFile("resourses/desk.png")) {
			std::cout << "can't load desk texture" << std::endl;
		}
		if (!figure_textures.loadFromFile("resourses/figures.png")) {
			std::cout << "can't load figure textures" << std::endl;
		}

		figure_textures.setSmooth(true);

		desk_sprite.setTexture(desk_texture);
		desk_sprite.setScale((double)window.getSize().x / (double)desk_texture.getSize().x, 
			(double)window.getSize().y / (double)desk_texture.getSize().y);

		for (auto figure : desk->GetFigures(Color::White)) {
			sf::Sprite figure_sprite;
			figure_sprite.setTexture(figure_textures);
			figure_sprite.setTextureRect(sf::IntRect(1000 - (int)figure->GetType() * 200, (int)figure->GetColor() * 200, 200, 200));
			figure_sprite.setScale((double)80 / 200, (double)80 / 200);
			figure_sprite.setPosition(560 - (int)figure->GetPosition().hor * 80, 560 - (int)figure->GetPosition().ver * 80);
			figure_sprites.push_back(figure_sprite);
		}

		for (auto figure : desk->GetFigures(Color::Black)) {
			sf::Sprite figure_sprite;
			figure_sprite.setTexture(figure_textures);
			figure_sprite.setTextureRect(sf::IntRect(1000 - (int)figure->GetType() * 200, (int)figure->GetColor() * 200, 200, 200));
			figure_sprite.setScale((double)80 / 200, (double)80 / 200);
			figure_sprite.setPosition(560 - (int)figure->GetPosition().hor * 80, 560 - (int)figure->GetPosition().ver * 80);
			figure_sprites.push_back(figure_sprite);
		}

		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}

			window.clear();
			window.draw(desk_sprite);
			for (auto sprite : figure_sprites) {
				window.draw(sprite);
			}
			window.display();

			this_thread::sleep_for(std::chrono::milliseconds(100));
		}
	}


};