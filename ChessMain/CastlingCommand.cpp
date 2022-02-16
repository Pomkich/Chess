#include "CastlingCommand.h"

bool CastlingCommand::Execute(std::shared_ptr<Desk> desk) {
	shared_ptr<Figure> rook;
	shared_ptr<Figure> king;
	list<shared_ptr<Figure>> other_figures;

	std::tie(rook, king, other_figures) = TryGetFigures(desk);	// getting figures depending on flank and color

	if (rook == nullptr || king == nullptr) {
		cout << "can't find a figure in cell in CastlingCommand::Execute" << endl;
		return false;
	}
	if (rook->IsWalked() || king->IsWalked()) {
		cout << "one of the figure (or both) already walked in CastlingCommand::Execute" << endl;
		return false;
	}

	for (auto figure : other_figures) {
		if (figure != nullptr) {
			cout << "figure on way of castling in CastlingCommand::Execute" << endl;
			return false;
		}
	}

	if (CellsIsAttacked(desk)) {
		cout << "can't castling while cells is attacked in CastlingCommand::Execute" << endl;
		return false;
	}

	// moving figures as required
	switch (color) {
	case Color::White:

		switch (flank) {
		case Flank::Queen:
			desk->MoveFigure(Coordinate(Horizontal::E, Vertical::One), Coordinate(Horizontal::C, Vertical::One));
			desk->MoveFigure(Coordinate(Horizontal::A, Vertical::One), Coordinate(Horizontal::D, Vertical::One));
			break;

		case Flank::King:
			desk->MoveFigure(Coordinate(Horizontal::E, Vertical::One), Coordinate(Horizontal::G, Vertical::One));
			desk->MoveFigure(Coordinate(Horizontal::H, Vertical::One), Coordinate(Horizontal::F, Vertical::One));
			break;
		}
		break;

	case Color::Black:
		switch (flank) {
		case Flank::Queen:
			desk->MoveFigure(Coordinate(Horizontal::E, Vertical::One), Coordinate(Horizontal::C, Vertical::Eigth));
			desk->MoveFigure(Coordinate(Horizontal::A, Vertical::One), Coordinate(Horizontal::D, Vertical::Eigth));
			break;

		case Flank::King:
			desk->MoveFigure(Coordinate(Horizontal::E, Vertical::One), Coordinate(Horizontal::G, Vertical::Eigth));
			desk->MoveFigure(Coordinate(Horizontal::H, Vertical::One), Coordinate(Horizontal::F, Vertical::Eigth));
			break;
		}
		break;
	}
};

// trying to find attacked cell depending on flank and color
bool CastlingCommand::CellsIsAttacked(std::shared_ptr<Desk> desk) {
	set<Coordinate> enemy_attacked_cells;
	list<Coordinate> found_cells;

	switch (color) {
	case Color::White:
		enemy_attacked_cells = desk->GetAttackedCells(Color::Black);

		switch (flank) {
		case Flank::Queen:
			if (find(enemy_attacked_cells.begin(), enemy_attacked_cells.end(),
				Coordinate(Horizontal::B, Vertical::One)) != enemy_attacked_cells.end()) {
				found_cells.push_back(Coordinate(Horizontal::B, Vertical::One));
			}
			if (find(enemy_attacked_cells.begin(), enemy_attacked_cells.end(),
				Coordinate(Horizontal::C, Vertical::One)) != enemy_attacked_cells.end()) {
				found_cells.push_back(Coordinate(Horizontal::B, Vertical::One));
			}
			if (find(enemy_attacked_cells.begin(), enemy_attacked_cells.end(),
				Coordinate(Horizontal::D, Vertical::One)) != enemy_attacked_cells.end()) {
				found_cells.push_back(Coordinate(Horizontal::B, Vertical::One));
			}
			break;

		case Flank::King:
			if (find(enemy_attacked_cells.begin(), enemy_attacked_cells.end(),
				Coordinate(Horizontal::F, Vertical::One)) != enemy_attacked_cells.end()) {
				found_cells.push_back(Coordinate(Horizontal::B, Vertical::One));
			}
			if (find(enemy_attacked_cells.begin(), enemy_attacked_cells.end(),
				Coordinate(Horizontal::G, Vertical::One)) != enemy_attacked_cells.end()) {
				found_cells.push_back(Coordinate(Horizontal::B, Vertical::One));
			}
			break;
		}

		break;

	case Color::Black:
		enemy_attacked_cells = desk->GetAttackedCells(Color::White);

		switch (flank) {
		case Flank::Queen:
			if (find(enemy_attacked_cells.begin(), enemy_attacked_cells.end(),
				Coordinate(Horizontal::B, Vertical::One)) != enemy_attacked_cells.end()) {
				found_cells.push_back(Coordinate(Horizontal::B, Vertical::Eigth));
			}
			if (find(enemy_attacked_cells.begin(), enemy_attacked_cells.end(),
				Coordinate(Horizontal::C, Vertical::One)) != enemy_attacked_cells.end()) {
				found_cells.push_back(Coordinate(Horizontal::B, Vertical::Eigth));
			}
			if (find(enemy_attacked_cells.begin(), enemy_attacked_cells.end(),
				Coordinate(Horizontal::D, Vertical::One)) != enemy_attacked_cells.end()) {
				found_cells.push_back(Coordinate(Horizontal::B, Vertical::Eigth));
			}
			break;

		case Flank::King:
			if (find(enemy_attacked_cells.begin(), enemy_attacked_cells.end(),
				Coordinate(Horizontal::F, Vertical::One)) != enemy_attacked_cells.end()) {
				found_cells.push_back(Coordinate(Horizontal::B, Vertical::Eigth));
			}
			if (find(enemy_attacked_cells.begin(), enemy_attacked_cells.end(),
				Coordinate(Horizontal::G, Vertical::One)) != enemy_attacked_cells.end()) {
				found_cells.push_back(Coordinate(Horizontal::B, Vertical::Eigth));
			}
			break;
		}
		break;
	}
	
	return !found_cells.empty();
}

// stupid, but understandable
tuple<shared_ptr<Figure>, shared_ptr<Figure>, list<shared_ptr<Figure>>> CastlingCommand::TryGetFigures(std::shared_ptr<Desk> desk) {
	shared_ptr<Figure> rook;
	shared_ptr<Figure> king;
	list<shared_ptr<Figure>> other_figures;

	switch (color) {

	case Color::White:
		king = desk->GetFigure(Coordinate(Horizontal::E, Vertical::One));

		switch (flank) {
		case Flank::Queen:
			rook = desk->GetFigure(Coordinate(Horizontal::A, Vertical::One));
			other_figures.push_back(desk->GetFigure(Coordinate(Horizontal::B, Vertical::One)));
			other_figures.push_back(desk->GetFigure(Coordinate(Horizontal::C, Vertical::One)));
			other_figures.push_back(desk->GetFigure(Coordinate(Horizontal::D, Vertical::One)));
			break;
		case Flank::King:
			rook = desk->GetFigure(Coordinate(Horizontal::H, Vertical::One));
			other_figures.push_back(desk->GetFigure(Coordinate(Horizontal::F, Vertical::One)));
			other_figures.push_back(desk->GetFigure(Coordinate(Horizontal::G, Vertical::One)));
			break;
		}
		break;

	case Color::Black:
		king = desk->GetFigure(Coordinate(Horizontal::E, Vertical::Eigth));

		switch (flank) {
		case Flank::Queen:
			rook = desk->GetFigure(Coordinate(Horizontal::A, Vertical::One));
			other_figures.push_back(desk->GetFigure(Coordinate(Horizontal::B, Vertical::Eigth)));
			other_figures.push_back(desk->GetFigure(Coordinate(Horizontal::C, Vertical::Eigth)));
			other_figures.push_back(desk->GetFigure(Coordinate(Horizontal::D, Vertical::Eigth)));
			break;
		case Flank::King:
			rook = desk->GetFigure(Coordinate(Horizontal::H, Vertical::One));
			other_figures.push_back(desk->GetFigure(Coordinate(Horizontal::F, Vertical::Eigth)));
			other_figures.push_back(desk->GetFigure(Coordinate(Horizontal::G, Vertical::Eigth)));
			break;
		}
		break;
	}

	return tuple<shared_ptr<Figure>, shared_ptr<Figure>, list<shared_ptr<Figure>>>(rook, king, other_figures);
}