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

	const int field_width = 100;
	const int field_height = 100;

public:
	SfmlControlManager();
	void InitResources();
	void inputThread();
	std::shared_ptr<sf::Sprite> GetSprite(Color color, sf::Vector2i pos);
	

};