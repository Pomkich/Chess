#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>
#include <chrono>
#include "Chess.h"
#include "Presenter.h"

class SfmlControlManager : public Presenter, public enable_shared_from_this<SfmlControlManager> {
	sf::RenderWindow window;
	sf::Texture desk_texture;
	sf::Texture figure_textures;
	sf::Sprite desk_sprite;
	std::array<std::vector<std::shared_ptr<sf::Sprite>>, 2> figure_sprites;

	std::shared_ptr<Chess> game;
	std::shared_ptr<Desk> desk;

	const int field_width = 100;
	const int field_height = 100;

public:
	SfmlControlManager();
	void InitResources();
	void InitPointers();
	void inputThread();
	void Run();
	std::shared_ptr<sf::Sprite> GetSprite(Color color, sf::Vector2i pos);
	
	virtual void NotifyGameStarted() override;
	virtual void NotifyKingShah(Color oposite_color) override;
	virtual void NotifyGameEnd(FinalState state) override;
	virtual void NotifyFigureMoved() override;
	virtual void NotifyFigureDeleted() override;

};