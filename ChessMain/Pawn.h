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

	void CheckSideCells(const array<array<Cell, field_size>, field_size> figures) {
		list<pair<int, int>> side_vectors;
		if (color == Color::White) {
			side_vectors = { {1, 1}, {-1, 1} };
		}
		else {
			side_vectors = { {1, -1}, {-1, -1} };
		}
	}
	// Pawn can attack side cells, but but moves only forward
	virtual void CalculateAttackedCells(const array<array<Cell, field_size>, field_size> desk) override {
		move_cells.clear();
		
	}
};