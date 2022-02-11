#include "Desk.h"

Desk::Desk() {
	cout << "desk created" << endl;
	// for test
	shared_ptr<Figure> pawn = make_shared<Pawn>(Color::White);
	pawn->SetPosition(Coordinate(Horizontal::A, Vertical::Two));
	figures[0].push_back(pawn);
	/////////////
}

void Desk::CalculateAttackedCells(Color col) {
	cout << "attacked cells of player " << (int)col << " calculated" << endl;
}

set<Coordinate> Desk::GetAttackedCells(Color col) {
	cout << "here is attacked cells of player " << (int)col << endl;
	return set<Coordinate>();
}

unique_ptr<Figure> Desk::GetFigure(const Coordinate figure_pos) {
	cout << "here is figure in cell" << endl;
	return unique_ptr<Figure>();
}

list<unique_ptr<Figure>> Desk::GetFigures(Color col) {
	cout << "here is figures on the desk" << endl;
	return list<unique_ptr<Figure>>();
}

void Desk::Draw() {
	list<shared_ptr<Figure>> all_figures = figures[0];
	all_figures.insert(all_figures.end(), figures[1].begin(), figures[1].end());

	cout << "     A   B   C   D   E   F   G   H  " << endl;
	for (int y = 0; y < 8; y++) {
		cout << "   .___.___.___.___.___.___.___.___." << endl;
		cout << y + 1 << "  ";
		for (int x = 0; x < 8; x++) {
			Coordinate temp_coord((Horizontal)x, (Vertical)y);
			auto temp_figure = find_if(all_figures.begin(), all_figures.end(),	// trying to find figure in cell
				[&](const shared_ptr<Figure> fig) { return Coordinate::Compare(temp_coord, fig->GetPosition()); }
			);		// ! very bad performance, but with i dont know how to implement this in console, with GUI would be better !

			if (temp_figure != all_figures.end()) {
				cout << "|" << (int)temp_figure->get()->GetColor() << (int)temp_figure->get()->GetType() << " ";
			}
			else {
				cout << "|   ";
			}
		}
		cout << "|" << endl;
	}
	cout << "   .___.___.___.___.___.___.___.___." << endl;
}
