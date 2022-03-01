#include "SfmlControlManager.h"

SfmlControlManager::SfmlControlManager() {
	
}

void SfmlControlManager::Run() {
	game->StartNewGame();
}

void SfmlControlManager::InitPointers() {
	desk = make_shared<Desk>();
	game = make_shared<Chess>(desk, shared_from_this());
}

void SfmlControlManager::InitResources() {
	// load textures
	if (!desk_texture.loadFromFile("resourses/desk.png")) {
		std::cout << "can't load desk texture" << std::endl;
	}
	if (!figure_textures.loadFromFile("resourses/figures.png")) {
		std::cout << "can't load figure textures" << std::endl;
	}

	figure_textures.setSmooth(true);
	// setting sprites
	desk_sprite.setTexture(desk_texture);
	desk_sprite.setScale((double)field_width * 8 / (double)desk_texture.getSize().x,
		(double)field_height * 8 / (double)desk_texture.getSize().y);

	for (int color = 0; color < 2; color++) {
		const int texture_width = figure_textures.getSize().x;
		const int texture_height = figure_textures.getSize().y;
		const int figure_width = texture_width / 6;	// because here is only 6 figures
		const int figure_heigth = texture_height / 2;	// because only two colors

		list<shared_ptr<Figure>> figures = desk->GetFigures((Color)color);
		if (figures.empty()) continue;

		for (auto figure : figures) {
			shared_ptr<sf::Sprite> figure_sprite = std::make_shared<sf::Sprite>();
			figure_sprite->setTexture(figure_textures);

			figure_sprite->setTextureRect(sf::IntRect(
				texture_width - figure_width - (int)figure->GetType() * figure_width,
				(int)figure->GetColor() * figure_heigth, figure_width, figure_heigth));
			// resize for desk size
			figure_sprite->setScale((double)field_width / figure_width, (double)field_height / figure_heigth);
			//field_width * 7 - (int)figure->GetPosition().hor * field_width,
			//field_height * 7 - (int)figure->GetPosition().ver * field_height
			figure_sprite->setPosition(
				field_width * 7 - (int)figure->GetPosition().hor * field_width,
				field_height * 7 - (int)figure->GetPosition().ver * field_height);
			figures_with_sprites[color].push_back(std::make_pair(figure_sprite, figure));
		}
	}
}

void SfmlControlManager::inputThread() {
	window.create(sf::VideoMode(field_width * 8, field_height * 8), "Chess");
	std::pair<std::shared_ptr<sf::Sprite>, std::shared_ptr<Figure>> draged_figure;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			else if (event.type == sf::Event::MouseButtonPressed) {
				auto figure = GetFigureWithSprite(game->GetTurnColor(), sf::Mouse::getPosition(window));
				if (figure.first != nullptr) {
					draged_figure = figure;
				}
			}
			else if (event.type == sf::Event::MouseButtonReleased && draged_figure.first != nullptr) {
				//draged_figure.first->setPosition(
				//	((int)draged_figure.first->getPosition().x + (int)draged_figure.first->getGlobalBounds().width / 2) / field_width * field_width,
				//	((int)draged_figure.first->getPosition().y + (int)draged_figure.first->getGlobalBounds().height / 2) / field_height * field_height);
				Coordinate drop_coord(
					(Horizontal)(7 - ((int)draged_figure.first->getPosition().x + (int)draged_figure.first->getGlobalBounds().width / 2) / field_width),
					(Vertical)(7 - ((int)draged_figure.first->getPosition().y + (int)draged_figure.first->getGlobalBounds().height / 2) / field_height));
				GenerateCommand(draged_figure.second->GetPosition(), drop_coord, game->GetTurnColor());
				draged_figure.first.reset();
			}
		}
		// follow for cursor
		if (draged_figure.first != nullptr) {
			draged_figure.first->setPosition(
				sf::Mouse::getPosition(window).x - draged_figure.first->getGlobalBounds().width / 2,
				sf::Mouse::getPosition(window).y - draged_figure.first->getGlobalBounds().height / 2);
		}

		window.clear();
		window.draw(desk_sprite);
		for (auto sprite : figures_with_sprites[0]) {
			window.draw(*sprite.first);
		}
		for (auto sprite : figures_with_sprites[1]) {
			window.draw(*sprite.first);
		}
		window.display();

		this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}

std::pair<std::shared_ptr<sf::Sprite>, std::shared_ptr<Figure>> 
	SfmlControlManager::GetFigureWithSprite(Color color, sf::Vector2i pos) {
	for (auto figure : figures_with_sprites[(int)color]) {
		if (figure.first->getGlobalBounds().contains(pos.x, pos.y)) {
			return figure;
		}
	}
	return std::pair<std::shared_ptr<sf::Sprite>, std::shared_ptr<Figure>>();
}

void SfmlControlManager::RefreshPositions() {
	for (int color = 0; color < 2; color++) {
		for (auto figure : figures_with_sprites[color]) {
			figure.first->setPosition(
				field_width * 7 - (int)figure.second->GetPosition().hor * field_width,
				field_height * 7 - (int)figure.second->GetPosition().ver * field_height);
		}
	}
}

void SfmlControlManager::GenerateCommand(Coordinate from, Coordinate to, Color color) {
	shared_ptr<Command> command;
	auto rook = desk->GetFigure(to);
	// for white figures castling
	if (from == Coordinate(Horizontal::E, Vertical::One) &&
		desk->GetFigure(from)->GetType() == FigureType::King) {	// if touched king in his base position
		if (rook != nullptr && rook->GetType() == FigureType::Rook) {	// and then if side cell has rook
			if (to == Coordinate(Horizontal::A, Vertical::One)) {
				command = make_shared<CastlingCommand>(Flank::Queen, color);
			}
			else if (to == Coordinate(Horizontal::H, Vertical::One)) {
				command = make_shared<CastlingCommand>(Flank::King, color);
			}
		}
	}
	// for black figures castling
	else if (from == Coordinate(Horizontal::E, Vertical::Eigth) &&
		desk->GetFigure(from)->GetType() == FigureType::King) {
		if (rook != nullptr && rook->GetType() == FigureType::Rook) {
			if (to == Coordinate(Horizontal::A, Vertical::Eigth)) {
				command = make_shared<CastlingCommand>(Flank::Queen, color);
			}
			else if (to == Coordinate(Horizontal::H, Vertical::Eigth)) {
				command = make_shared<CastlingCommand>(Flank::King, color);
			}
		}
	}
	
	if (command == nullptr) {
		command = make_shared<MoveCommand>(from, to, color);
	}
	command_holder->SetCommand(command);
}

void SfmlControlManager::NotifyGameStarted() {
	cout << "game started" << endl;

	InitResources();

	std::thread input_thr(&SfmlControlManager::inputThread, shared_from_this());
	input_thr.detach();
}

void SfmlControlManager::NotifyKingShah(Color oposite_color) {
	cout << "shah" << endl;
	RefreshPositions();
}

void SfmlControlManager::NotifyGameEnd(FinalState state) {
	cout << "game end" << endl;
	RefreshPositions();
}

void SfmlControlManager::NotifyFigureMoved() {
	RefreshPositions();
	cout << "figure moved" << endl;
}

void SfmlControlManager::NotifyFigureDeleted(Color color) {
	for (auto it = figures_with_sprites[(int)color].begin(); it != figures_with_sprites[(int)color].end(); it++) {
		if (it->second.use_count() == 1) {
			it->second.reset();
			it->first.reset();
			figures_with_sprites[(int)color].erase(it);
			break;
		}
	}
	RefreshPositions();
}

void SfmlControlManager::NotifyBadCommand() {
	cout << "bad command" << endl;
	RefreshPositions();
}
