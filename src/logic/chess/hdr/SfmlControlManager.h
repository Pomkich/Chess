#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>
#include <chrono>
#include "Chess.h"
#include "Presenter.h"

extern mutex mut;
extern condition_variable running_cv;
extern bool running_bool;

enum class AppState {
	Game, End
};

class SfmlControlManager : public Presenter, public enable_shared_from_this<SfmlControlManager> {
	AppState app_state;
	sf::RenderWindow window;
	sf::Texture desk_texture;
	sf::Texture figure_textures;
	sf::Sprite desk_sprite;
	std::array<std::vector<std::pair<std::shared_ptr<sf::Sprite>, std::shared_ptr<Figure>>>, 2> figures_with_sprites;

	sf::RectangleShape end_game_field;
	sf::RectangleShape new_game_button;
	sf::Font times_new_roman;
	sf::Text end_game_message;
	sf::Text new_game_text;

	std::shared_ptr<Chess> game;
	std::shared_ptr<Desk> desk;

	std::mutex render_mutex;

	const int field_width = 100;
	const int field_height = 100;

public:
	SfmlControlManager();
	void InitResources();
	void InitFigures();
	void InitPointers();
	void inputThread();
	void Run();
	std::pair<std::shared_ptr<sf::Sprite>, std::shared_ptr<Figure>> GetFigureWithSprite(Color color, sf::Vector2i pos);
	void RefreshPositions();
	void GenerateCommand(Coordinate from, Coordinate to, Color color);

	virtual void NotifyPawnReachedEnd(Coordinate coord, Color color) override;
	virtual void NotifyGameStarted() override;
	virtual void NotifyKingShah(Color oposite_color) override;
	virtual void NotifyGameEnd(FinalState state) override;
	virtual void NotifyFigureMoved() override;
	virtual void NotifyFigureDeleted(Color color) override;
	virtual void NotifyBadCommand() override;

};