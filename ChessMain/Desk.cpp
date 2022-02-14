#include "Desk.h"

Desk::Desk() {
}

void Desk::PlaceDefaultFigures() {
	// placing Pawns
	for (int i = 0; i < field_size; i++) {
		PlaceFigure(FigureType::Pawn, Color::White, Coordinate((Horizontal)i, Vertical::Two));
		PlaceFigure(FigureType::Pawn, Color::Black, Coordinate((Horizontal)i, Vertical::Seven));
	}

	PlaceFigure(FigureType::Rook, Color::White, Coordinate(Horizontal::A, Vertical::One));
	PlaceFigure(FigureType::Rook, Color::White, Coordinate(Horizontal::H, Vertical::One));
	PlaceFigure(FigureType::Rook, Color::Black, Coordinate(Horizontal::A, Vertical::Eigth));
	PlaceFigure(FigureType::Rook, Color::Black, Coordinate(Horizontal::H, Vertical::Eigth));

	PlaceFigure(FigureType::Horse, Color::White, Coordinate(Horizontal::B, Vertical::One));
	PlaceFigure(FigureType::Horse, Color::White, Coordinate(Horizontal::G, Vertical::One));
	PlaceFigure(FigureType::Horse, Color::Black, Coordinate(Horizontal::B, Vertical::Eigth));
	PlaceFigure(FigureType::Horse, Color::Black, Coordinate(Horizontal::G, Vertical::Eigth));

	PlaceFigure(FigureType::Bishop, Color::White, Coordinate(Horizontal::C, Vertical::One));
	PlaceFigure(FigureType::Bishop, Color::White, Coordinate(Horizontal::F, Vertical::One));
	PlaceFigure(FigureType::Bishop, Color::Black, Coordinate(Horizontal::C, Vertical::Eigth));
	PlaceFigure(FigureType::Bishop, Color::Black, Coordinate(Horizontal::F, Vertical::Eigth));

	PlaceFigure(FigureType::Queen, Color::White, Coordinate(Horizontal::D, Vertical::One));
	PlaceFigure(FigureType::King, Color::White, Coordinate(Horizontal::E, Vertical::One));

	PlaceFigure(FigureType::Queen, Color::Black, Coordinate(Horizontal::D, Vertical::Eigth));
	PlaceFigure(FigureType::King, Color::Black, Coordinate(Horizontal::E, Vertical::Eigth));
}

void Desk::CalculateAttackedCells() {
	// calculating white cells
	for (auto figure : figures[(int)Color::White]) {
		figure->CalculateAttackedCells(field);
		for (auto cell : figure->GetMoveCells()) {
			attacked_cells[(int)Color::White].insert(cell);
		}
	}
	// calculating black cells
	for (auto figure : figures[(int)Color::Black]) {
		figure->CalculateAttackedCells(field);
		for (auto cell : figure->GetMoveCells()) {
			attacked_cells[(int)Color::Black].insert(cell);
		}
	}
}

set<Coordinate> Desk::GetAttackedCells(Color col) {
	return attacked_cells[(int)col];
}

void Desk::PlaceFigure(FigureType type, Color color, Coordinate pos) {
	int hor = (int)pos.hor, ver = (int)pos.ver;
	if (!Coordinate::InBounds(hor, ver)) {
		cout << "out of bounds in Desk::PlaceFigure" << endl;
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
		ptr_fig = make_shared<Rook>(color);
		break;
	case FigureType::Queen:
		ptr_fig = make_shared<Queen>(color);
		break;
	case FigureType::King:
		ptr_fig = make_shared<King>(color);
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

shared_ptr<Figure> Desk::GetFigure(const Coordinate figure_pos) {
	list<shared_ptr<Figure>> all_figures = figures[0];
	all_figures.insert(all_figures.end(), figures[1].begin(), figures[1].end());

	auto figure = find_if(all_figures.begin(), all_figures.end(),
		[figure_pos](shared_ptr<Figure> fig) { return Coordinate::Compare(figure_pos, fig->GetPosition()); });

	if (figure == all_figures.end()) {
		return shared_ptr<Figure>();	// nullptr
	}
	return *figure;
}
// must delete figures (?) no
void Desk::MoveFigure(Coordinate from, Coordinate to) {
	shared_ptr<Figure> figure = GetFigure(from);
	shared_ptr<Figure> side_figure = GetFigure(to);
	// if figure in 'from' coordinate found and 'to' coordinate has no figure
	if (figure != nullptr && side_figure == nullptr) {
		pair<int, int> coord_from = from.ToInt();
		pair<int, int> coord_to = to.ToInt();

		field[coord_from.second][coord_from.first].has_figure = false;
		field[coord_to.second][coord_to.first].has_figure = true;
		field[coord_to.second][coord_to.first].color = figure->GetColor();
		field[coord_to.second][coord_to.first].type = figure->GetType();
		figure->SetPosition(to);
	}
	else {
		cout << "cell don't have a figure or second cell has a figure" << endl;
	}
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