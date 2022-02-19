#include "MoveCommand.h"

bool MoveCommand::Execute(std::shared_ptr<Desk> desk) {
	// if cell in moving_cells of figure
		// if figure moving in empty cell -> just move
		// if figure moving in not empty cell -> check enemy figure
		//		if yes -> delete enemy figure -> move
		//		if no -> bad command, return false
	auto figure = desk->GetFigure(from);

	if (figure == nullptr) {
		cout << "cell don't have a figure in MoveCommand::Execute" << endl;
		return false;
	}
	else if (figure->GetColor() != color) {
		cout << "can't move enemy figure in MoveCommand::Execute" << endl;
		return false;
	}

	list<Coordinate> move_cells = figure->GetMoveCells();
	if (find(move_cells.begin(), move_cells.end(), to) == move_cells.end()) {
		cout << "figure can't move to the cell according to the rules in MoveCommand::Execute" << endl;
		return false;
	}

	auto sec_figure = desk->GetFigure(to);
	// if cell has a figure and this is enemy figure
	if (sec_figure != nullptr && sec_figure->GetColor() != color) {
		desk->DeleteFigure(to);
		delete_figure = true;
		deleted_figure_type = sec_figure->GetType();
	}
	desk->MoveFigure(from, to);

	if (!figure->IsWalked()) {
		figure->SetWalked(true);
	}

	executed = true;
}

void MoveCommand::Cansel(shared_ptr<Desk> desk) {
	if (!executed) {
		cout << "can't cansel not executed command in MoveCommand::Cansel" << endl;
		return;
	}

	desk->MoveFigure(to, from);
	if (delete_figure) {
		if (color == Color::White) {
			desk->PlaceFigure(deleted_figure_type, Color::Black, to);
		}
		else {
			desk->PlaceFigure(deleted_figure_type, Color::White, to);
		}
	}
}