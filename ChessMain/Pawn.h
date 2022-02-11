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
			move_vectors = { {0, 1} };
		}
		else {
			move_vectors = { {0, -1} };
		}
	}

	void CheckSideCells(const array<array<Cell, field_size>, field_size> desk) {
		list<pair<int, int>> side_vectors;
		if (color == Color::White) {
			side_vectors = { {1, 1}, {-1, 1} };
		}
		else {
			side_vectors = { {1, -1}, {-1, -1} };
		}

		for (pair<int, int> vec : side_vectors) {
			int hor = (int)current_pos.hor, ver = (int)current_pos.ver;
			hor += vec.first;
			ver += vec.second;

			if ((hor >= 0 && hor <= 7) && (ver >= 0 && ver <= 7)) {	// if in bounds
				if (desk[ver][hor].has_figure && desk[ver][hor].color != color) {	// if cell has enemy figure
					move_cells.push_back(Coordinate((Horizontal)hor, (Vertical)ver));
				}
			}
		}
	}
	// Pawn can attack side cells, but but moves only forward
	virtual void CalculateAttackedCells(const array<array<Cell, field_size>, field_size> desk) override {
		move_cells.clear();
		CheckSideCells(desk);

		int hor = (int)current_pos.hor, ver = (int)current_pos.ver;
		hor += move_vectors.front().first;	// pawn can move only forward, so here is one vector in begining
		ver += move_vectors.front().second;

		if ((hor >= 0 && hor <= 7) && (ver >= 0 && ver <= 7)) {	// if in bounds
			if (!desk[ver][hor].has_figure) {	// if cell dont have figure
				move_cells.push_back(Coordinate((Horizontal)hor, (Vertical)ver));

				if (!walked) {	// pawn can make two steps at first turn
					hor += move_vectors.front().first;
					ver += move_vectors.front().second;

					if ((hor >= 0 && hor <= 7) && (ver >= 0 && ver <= 7)) {	// if in bounds
						if (!desk[ver][hor].has_figure) {	// if cell dont have figure
							move_cells.push_back(Coordinate((Horizontal)hor, (Vertical)ver));
						}
					}
				}
			}
		}
	}
};