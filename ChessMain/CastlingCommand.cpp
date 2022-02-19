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
			king_from = Coordinate(Horizontal::E, Vertical::One); king_to = Coordinate(Horizontal::C, Vertical::One);
			rook_from = Coordinate(Horizontal::A, Vertical::One); rook_to = Coordinate(Horizontal::D, Vertical::One);
			break;

		case Flank::King:
			king_from = Coordinate(Horizontal::E, Vertical::One); king_to = Coordinate(Horizontal::G, Vertical::One);
			rook_from = Coordinate(Horizontal::H, Vertical::One); rook_to = Coordinate(Horizontal::F, Vertical::One);
			break;
		}
		break;

	case Color::Black:
		switch (flank) {
		case Flank::Queen:
			king_from = Coordinate(Horizontal::E, Vertical::Eigth); king_to = Coordinate(Horizontal::C, Vertical::Eigth);
			rook_from = Coordinate(Horizontal::A, Vertical::Eigth); rook_to = Coordinate(Horizontal::D, Vertical::Eigth);
			break;

		case Flank::King:
			king_from = Coordinate(Horizontal::E, Vertical::Eigth); king_to = Coordinate(Horizontal::G, Vertical::Eigth);
			rook_from = Coordinate(Horizontal::H, Vertical::Eigth); rook_to = Coordinate(Horizontal::F, Vertical::Eigth);
			break;
		}
		break;
	}

	desk->MoveFigure(king_from, king_to);
	desk->MoveFigure(rook_from, rook_to);
	king->SetWalked(true);
	rook->SetWalked(true);

	executed = true;

	return true;
};

bool CastlingCommand::Cansel(shared_ptr<Desk> desk) {
	if (!executed) {
		cout << "can't cansel not executed command in CastlingCommand::Cansel" << endl;
		return false;
	}

	desk->MoveFigure(king_to, king_from);
	desk->MoveFigure(rook_to, rook_from);
	desk->GetFigure(king_from)->SetWalked(false);
	desk->GetFigure(rook_from)->SetWalked(false);

	return true;
}

// trying to find attacked cell depending on flank and color
bool CastlingCommand::CellsIsAttacked(std::shared_ptr<Desk> desk) {
	set<Coordinate> enemy_attacked_cells;

	switch (color) {
	case Color::White:
		enemy_attacked_cells = desk->GetAttackedCells(Color::Black);

		switch (flank) {
		case Flank::Queen:
			if (find(enemy_attacked_cells.begin(), enemy_attacked_cells.end(),
				Coordinate(Horizontal::B, Vertical::One)) != enemy_attacked_cells.end()) {
				return true;
			}
			if (find(enemy_attacked_cells.begin(), enemy_attacked_cells.end(),
				Coordinate(Horizontal::C, Vertical::One)) != enemy_attacked_cells.end()) {
				return true;
			}
			if (find(enemy_attacked_cells.begin(), enemy_attacked_cells.end(),
				Coordinate(Horizontal::D, Vertical::One)) != enemy_attacked_cells.end()) {
				return true;
			}
			break;

		case Flank::King:
			if (find(enemy_attacked_cells.begin(), enemy_attacked_cells.end(),
				Coordinate(Horizontal::F, Vertical::One)) != enemy_attacked_cells.end()) {
				return true;
			}
			if (find(enemy_attacked_cells.begin(), enemy_attacked_cells.end(),
				Coordinate(Horizontal::G, Vertical::One)) != enemy_attacked_cells.end()) {
				return true;
			}
			break;
		}

		break;

	case Color::Black:
		enemy_attacked_cells = desk->GetAttackedCells(Color::White);

		switch (flank) {
		case Flank::Queen:
			if (find(enemy_attacked_cells.begin(), enemy_attacked_cells.end(),
				Coordinate(Horizontal::B, Vertical::Eigth)) != enemy_attacked_cells.end()) {
				return true;
			}
			if (find(enemy_attacked_cells.begin(), enemy_attacked_cells.end(),
				Coordinate(Horizontal::C, Vertical::Eigth)) != enemy_attacked_cells.end()) {
				return true;
			}
			if (find(enemy_attacked_cells.begin(), enemy_attacked_cells.end(),
				Coordinate(Horizontal::D, Vertical::Eigth)) != enemy_attacked_cells.end()) {
				return true;
			}
			break;

		case Flank::King:
			if (find(enemy_attacked_cells.begin(), enemy_attacked_cells.end(),
				Coordinate(Horizontal::F, Vertical::Eigth)) != enemy_attacked_cells.end()) {
				return true;
			}
			if (find(enemy_attacked_cells.begin(), enemy_attacked_cells.end(),
				Coordinate(Horizontal::G, Vertical::Eigth)) != enemy_attacked_cells.end()) {
				return true;
			}
			break;
		}
		break;
	}
	
	return false;
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