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
	std::array<std::vector<std::shared_ptr<sf::Sprite>>, 2> figure_sprites;

	std::shared_ptr<Desk> desk;

public:
	SfmlControlManager() {
		desk = make_shared<Desk>();
		desk->PlaceDefaultFigures();

		const int field_width = 100;
		const int field_height = 100;

		window.create(sf::VideoMode(field_width * 8, field_height * 8), "Chess");
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

		for (int color = 0; color < 2; color++) {
			for (auto figure : desk->GetFigures((Color)color)) {
				shared_ptr<sf::Sprite> figure_sprite = std::make_shared<sf::Sprite>();
				figure_sprite->setTexture(figure_textures);

				const int texture_width = figure_textures.getSize().x;
				const int texture_height = figure_textures.getSize().y;
				const int figure_width = texture_width / 6;	// because here is only 6 figures
				const int figure_heigth = texture_height / 2;	// because only two colors

				figure_sprite->setTextureRect(sf::IntRect(
					texture_width - figure_width - (int)figure->GetType() * figure_width,
					(int)figure->GetColor() * figure_heigth, figure_width, figure_heigth));
				// resize for desk size
				figure_sprite->setScale((double)field_width / figure_width, (double)field_height / figure_heigth);
				figure_sprite->setPosition(
					field_width * 7 - (int)figure->GetPosition().hor * field_width,
					field_height * 7 - (int)figure->GetPosition().ver * field_height);
				figure_sprites[color].push_back(figure_sprite);
			}
		}

		std::shared_ptr<sf::Sprite> draged_figure;

		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
				else if (event.type == sf::Event::MouseButtonPressed) {
					std::cout << "button pressed" << std::endl;
					auto figure = GetSprite(Color::White, sf::Mouse::getPosition(window));
					if (figure != nullptr) {
						std::cout << "here is figure" << std::endl;;
						draged_figure = figure;
					}
				}
				else if (event.type == sf::Event::MouseButtonReleased && draged_figure != nullptr) {
					draged_figure->setPosition(
						((int)draged_figure->getPosition().x + (int)draged_figure->getGlobalBounds().width / 2) / field_width * field_width,
						((int)draged_figure->getPosition().y + (int)draged_figure->getGlobalBounds().height / 2) / field_height * field_height);
					draged_figure.reset();
				}
			}
			if (draged_figure != nullptr) {
				draged_figure->setPosition(
					sf::Mouse::getPosition(window).x - draged_figure->getGlobalBounds().width / 2,
					sf::Mouse::getPosition(window).y - draged_figure->getGlobalBounds().height / 2);
			}

			window.clear();
			window.draw(desk_sprite);
			for (auto sprite : figure_sprites[0]) {
				window.draw(*sprite);
			}
			for (auto sprite : figure_sprites[1]) {
				window.draw(*sprite);
			}
			window.display();

			this_thread::sleep_for(std::chrono::milliseconds(10));
		}
	}

	std::shared_ptr<sf::Sprite> GetSprite(Color color, sf::Vector2i pos) {
		for (auto sprite : figure_sprites[(int)color]) {
			if (sprite->getGlobalBounds().contains(pos.x, pos.y)) {
				return sprite;
			}
		}
		return std::shared_ptr<sf::Sprite>();
	}


};