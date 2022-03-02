#pragma once
#include "Figure.h"

class King : public Figure {
public:
	King() {
		walked = false;
		type = FigureType::King;
		color = Color::White;
		move_vectors = {
			{1, 0}, {0, 1}, {-1, 0}, {0, -1},	// linear
			{1, 1}, {-1, 1}, {1, -1}, {-1, -1}	// diagonal
		};
	}

	King(Color col) {
		walked = false;
		type = FigureType::King;
		color = col;
		move_vectors = {
			{1, 0}, {0, 1}, {-1, 0}, {0, -1},	// linear
			{1, 1}, {-1, 1}, {1, -1}, {-1, -1}	// diagonal
		};
	}

	virtual void CalculateAttackedCells(const array<array<Cell, field_size>, field_size> desk) override {
		move_cells.clear();
		attack_cells.clear();
		for (auto move_vec : move_vectors) {
			pair<int, int> coord = current_pos.ToInt();
			coord.first += move_vec.first;
			coord.second += move_vec.second;
			if (Coordinate::InBounds(coord.first, coord.second)) {
				move_cells.push_back(Coordinate((Horizontal)coord.first, (Vertical)coord.second));
				attack_cells.push_back(Coordinate((Horizontal)coord.first, (Vertical)coord.second));
			}
		}
	}
};