#pragma once
#include "Figure.h"

class Queen : public Figure {
public:
	Queen() {
		type = FigureType::Queen;
		move_vectors = { 
			{1, 0}, {0, 1}, {-1, 0}, {0, -1},	// linear
			{1, 1}, {-1, 1}, {1, -1}, {-1, -1}	// diagonal
		};
	}

	virtual void CalculateAttackedCells(const array<array<Cell, field_size>, field_size> desk) override {
		move_cells.clear();
	}
};