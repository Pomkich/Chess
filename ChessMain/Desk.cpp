#include "Desk.h"

Desk::Desk() {
	cout << "desk created" << endl;
}

void Desk::CalculateAttackedCells(Color col) {
	cout << "attacked cells of player " << (int)col << " calculated" << endl;
}

set<Coordinate> Desk::GetAttackedCells(Color col) {
	cout << "here is attacked cells of player " << (int)col << endl;
	return set<Coordinate>();
}

// commented out until at least one derived Figure class has been created
/*unique_ptr<Figure> Desk::GetFigure(const Coordinate figure_pos) {
	return unique_ptr<Figure>();
}

list<unique_ptr<Figure>> Desk::GetFigures(Color col) {
	return list<unique_ptr<Figure>>();
}*/

void Desk::Draw() {
	cout << "here is your desk" << endl;
}
