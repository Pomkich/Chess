#include "DeskViewer.h"

// the method of checking the command, if it is successful, then the command is executed on a real desk
bool DeskViewer::CheckCommand(shared_ptr<Command> command, Color color) {
	/* pseudo code
if (command->Execute(this) != Command::BadCommand) {
	if (!KingUnderAttack(color)) {
		return true;
	}
	else {
		command->Cansel(this);
		return false;
	}
}
*/	return false;
}

// search for the check
bool DeskViewer::KingUnderAttack(Color color) {
	shared_ptr<Figure> king = virtual_desk->GetKing(color);

	// getting enemy attacked cells
	set<Coordinate> attacked_cells;
	if (color == Color::White) {
		attacked_cells = virtual_desk->GetAttackedCells(Color::Black);
	}
	else {
		attacked_cells = virtual_desk->GetAttackedCells(Color::White);
	}

	// check if king's position under attack
	for (auto cell : attacked_cells) {
		if (cell == king->GetPosition()) {
			return true;
		}
	}
	
	return false;
}

// search for checkmate
bool DeskViewer::KingCheckmate(Color color, shared_ptr<Figure> attacking_figure) {
	// if it Horse or Pawn -> check can kill him or king can move
	// if it not Horse or Pawn -> check can kill him or king can move or can block attack vector

	if (!KingUnderAttack(color)) return false;	// maybe should erase this string because components that will use this method will check it

	set<Coordinate> attacked_cells = virtual_desk->GetAttackedCells(color);
	
	// check king move
	auto king = virtual_desk->GetKing(color);
	if (!king->GetMoveCells().empty()) return false;
	// check can kill attacked figure
	for (auto cell : attacked_cells) {
		if (cell == attacking_figure->GetPosition()) {
			return false;
		}
	}
	// if it horse or pawn -> lose
	if (attacking_figure->GetType() != FigureType::Horse &&
		attacking_figure->GetType() != FigureType::Pawn) {
		auto cells_on_attack_vector = CalculateAttackVector(attacking_figure->GetPosition(), king->GetPosition());
		// trying to find turn, that can block attack vector;
		for (auto vec_cell : cells_on_attack_vector) {
			for (auto attacked_cell : attacked_cells) {
				if (vec_cell == attacked_cell) {
					return false;
				}
			}
		}
	}
	// if none of the conditions are met, the king is checkmated
	return true;
}

// search for pat
bool DeskViewer::KingPat(Color color) {
	if (KingUnderAttack(color)) return false;
	return virtual_desk->GetAttackedCells(color).empty();
}
// logic: calculate distance between figures, values in attack vector defines the direction in which you need to move to get 0
// when you get 0 - you steped on all cells on way to king
list<Coordinate> DeskViewer::CalculateAttackVector(Coordinate attack_figure_pos, Coordinate king_pos) {
	pair<int, int> attack_figure_int = attack_figure_pos.ToInt();
	pair<int, int> king_int = king_pos.ToInt();

	pair<int, int> attack_vector;
	attack_vector.first = king_int.first - attack_figure_int.first;
	attack_vector.second = king_int.second - attack_figure_int.second;
	// define moving direction
	pair<int, int> incrementer;
	if (attack_vector.first < 0)
		incrementer.first = 1;
	else if (attack_vector.first > 0)
		incrementer.first = -1;
	else incrementer.first = 0;

	if (attack_vector.second < 0)
		incrementer.second = 1;
	else if (attack_vector.second > 0)
		incrementer.second = -1;
	else incrementer.second = 0;

	list<Coordinate> cells;
	// moving to attack figure and mark cells on way to it
	while (attack_vector.first != 0 && attack_vector.second != 0) {
		attack_vector.first += incrementer.first;
		attack_vector.second += incrementer.second;
		cells.push_back(Coordinate((Horizontal)attack_vector.first, (Vertical)attack_vector.second));
	}

	return cells;
}