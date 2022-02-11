#pragma once
#include "Figure.h"

class Bishop: public Figure {
public:
	Bishop() {
		type = FigureType::Bishop;
		move_vectors = {
			{1, 1}, {-1, 1}, {1, -1}, {-1, -1}	// diagonal
		};
	}

	virtual void CalculateAttackedCells(const array<array<Cell, field_size>, field_size> desk) override {
		move_cells.clear();
	}
};