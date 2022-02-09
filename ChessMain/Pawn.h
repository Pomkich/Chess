#pragma once
#include "Figure.h"

class Pawn : public Figure {
private:
	bool walked;

public:
	Pawn(Color col) {
		type = FigureType::Pawn;
		color = col;
		walked = false;
		move_range = 1;

		if (color == Color::White) {
			move_vectors = { {1, 0} };
		}
		else {
			move_vectors = { {-1, 0} };
		}
	}

	void CheckSideCells(const list<shared_ptr<Figure>> figures) {
		list<pair<int, int>> side_vectors;
		if (color == Color::White) {
			side_vectors = { {1, 1}, {1, -1} };
		}
		else {
			side_vectors = { {-1, 1}, {-1, -1} };
		}

		for (auto vec : side_vectors) {
			int hor = (int)current_pos.hor, ver = (int)current_pos.ver;
			hor += vec.first;
			ver += vec.second;

			if ((hor <= 7 && hor >= 0) || (ver <= 7 && ver >= 0)) {	// check out of bounds
				Coordinate temp_coord((Horizontal)hor, (Vertical)ver);
				auto figure = find_if(figures.begin(), figures.end(),	// trying to find figure in side cell
					[&](const shared_ptr<Figure> fig) { return Coordinate::Compare(temp_coord, fig->GetPosition()); }
				);

				if (figure != figures.end() && figure->get()->GetColor() != color) {	// check if cell has an enemy figure
					move_cells.push_back(temp_coord);
				}
			}
		}
	}
	// Pawn can attack side cells, but but moves only forward
	virtual void CalculateAttackedCells(const list<shared_ptr<Figure>> figures) override {
		move_cells.clear();
		CheckSideCells(figures);

		int hor = (int)current_pos.hor, ver = (int)current_pos.ver;
		hor += move_vectors.front().first;
		ver += move_vectors.front().second;

		if ((hor <= 7 && hor >= 0) || (ver <= 7 && ver >= 0)) {	// check out of bounds
			Coordinate temp_coord((Horizontal)hor, (Vertical)ver);

			auto figure = find_if(figures.begin(), figures.end(),	// trying to find figure in cell
				[&](const shared_ptr<Figure> fig) {return Coordinate::Compare(temp_coord, fig->GetPosition()); }
			);

			if (figure == figures.end()) {	// if cell has no figure
				move_cells.push_back(temp_coord);
			}

			if (!walked) {	// if Pawn don't walked, she can make two steps at first turn
				hor += move_vectors.front().first;
				ver += move_vectors.front().second;

				temp_coord.hor = (Horizontal)hor;
				temp_coord.ver = (Vertical)ver;

				figure = find_if(figures.begin(), figures.end(),
					[&](const shared_ptr<Figure> fig) {return Coordinate::Compare(temp_coord, fig->GetPosition()); }
				);

				if (figure == figures.end()) {
					move_cells.push_back(temp_coord);
				}
			}
		}
	}
};