#include "Desk.h"

Desk::Desk() {
	cout << "desk created" << endl;

	PlaceFigure(FigureType::Bishop, Color::White, Coordinate(Horizontal::E, Vertical::Four));
	PlaceFigure(FigureType::Pawn, Color::White, Coordinate(Horizontal::C, Vertical::Two));
	PlaceFigure(FigureType::Pawn, Color::Black, Coordinate(Horizontal::G, Vertical::Two));
	figures[0].begin()->get()->CalculateAttackedCells(field);
	auto move_cell = figures[0].begin()->get()->GetMoveCells();
	for (auto cell : move_cell) {
		cout << cell;
	}
}

void Desk::CalculateAttackedCells(Color col) {
	cout << "attacked cells of player " << (int)col << " calculated" << endl;
}

set<Coordinate> Desk::GetAttackedCells(Color col) {
	cout << "here is attacked cells of player " << (int)col << endl;
	return set<Coordinate>();
}

void Desk::PlaceFigure(FigureType type, Color color, Coordinate pos) {
	int hor = (int)pos.hor, ver = (int)pos.ver;
	if ((hor < 0 && hor > 7) && (ver < 0 && ver > 7)) {	// if in bounds
		cout << "out of bouls in Desk::PlaceFigure" << endl;
		return;
	}
	if (field[ver][hor].has_figure) {
		cout << "cell already have a figure Desk::PlaceFigure" << endl;
		return;
	}

	shared_ptr<Figure> ptr_fig;

	switch (type) {
	case FigureType::Pawn:
		ptr_fig = make_shared<Pawn>(color);
		break;
	case FigureType::Horse:
		ptr_fig = make_shared<Horse>(color);
		break;
	case FigureType::Bishop:
		ptr_fig = make_shared<Bishop>(color);
		break;
	case FigureType::Rook:
		ptr_fig = make_shared<Rook>();
		break;
	default:
		cout << "can't create a non-existent figure in Desk::PlaceFigure" << endl;
		return;
	}

	figures[(int)color].push_back(ptr_fig);
	ptr_fig->SetPosition(pos);

	field[ver][hor].has_figure = true;
	field[ver][hor].type = type;
	field[ver][hor].color = color;
}

unique_ptr<Figure> Desk::GetFigure(const Coordinate figure_pos) {
	cout << "here is figure in cell" << endl;
	return unique_ptr<Figure>();
}

void Desk::Draw() {
	list<shared_ptr<Figure>> all_figures = figures[0];
	all_figures.insert(all_figures.end(), figures[1].begin(), figures[1].end());

	cout << "     A    B    C    D    E    F    G    H   " << endl;
	for (int y = 0; y < 8; y++) {
		cout << "   .____.____.____.____.____.____.____.____." << endl;
		cout << y + 1 << "  ";
		for (int x = 0; x < 8; x++) {
			if (field[y][x].has_figure) {
				cout << "| " << (int)field[y][x].color << (int)field[y][x].type << " ";
			}
			else {
				cout << "|    ";
			}
		}
		cout << "|" << endl;
	}
	cout << "   .____.____.____.____.____.____.____.____." << endl;
}


/*PlaceFigure(FigureType::Horse, Color::White, Coordinate(Horizontal::E, Vertical::Four));
	figures[0].begin()->get()->CalculateAttackedCells(field);
	auto move_cell = figures[0].begin()->get()->GetMoveCells();
	for (auto cell : move_cell) {
		cout << cell;
	}*/

	/*PlaceFigure(FigureType::Pawn, Color::White, Coordinate(Horizontal::B, Vertical::Two));
	PlaceFigure(FigureType::Pawn, Color::Black, Coordinate(Horizontal::A, Vertical::Three));
	PlaceFigure(FigureType::Pawn, Color::Black, Coordinate(Horizontal::C, Vertical::Three));
	PlaceFigure(FigureType::Rook, Color::Black, Coordinate(Horizontal::B, Vertical::Three));

	figures[0].begin()->get()->CalculateAttackedCells(field);
	auto move_cell = figures[0].begin()->get()->GetMoveCells();
	for (auto cell : move_cell) {
		cout << cell;
	}*/