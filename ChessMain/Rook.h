#pragma once
#include "Figure.h"

class Rook : public Figure {
private:
	bool walked;	// need for castling

public:
	Rook() {
		walked = false;
		type = FigureType::Rook;
		move_vectors = { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };	// linear
	}

	virtual void CalculateAttackedCells(const array<array<Cell, field_size>, field_size> desk) override {
		move_cells.clear();
	}
};