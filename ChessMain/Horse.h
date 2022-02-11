#pragma once
#include "Figure.h"

class Horse : public Figure {
public:
	Horse() {
		type = FigureType::Horse;
		move_vectors = {
			{2, 1}, {2, -1}, {-2, 1}, {-2, -1},
			{1, 2}, {-1, 2}, {1, -2}, {-1, -2}
		};
	}

	virtual void CalculateAttackedCells(const array<array<Cell, field_size>, field_size> desk) override {
		move_cells.clear();
	}
};