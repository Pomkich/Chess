#pragma once
#include "Figure.h"

class Horse : public Figure {
public:
	Horse() {
		type = FigureType::Horse;
		color = Color::White;
		move_vectors = {
			{2, 1}, {2, -1}, {-2, 1}, {-2, -1},
			{1, 2}, {-1, 2}, {1, -2}, {-1, -2}
		};
	}

	Horse(Color col) {
		type = FigureType::Horse;
		color = col;
		move_vectors = {
			{2, 1}, {2, -1}, {-2, 1}, {-2, -1},
			{1, 2}, {-1, 2}, {1, -2}, {-1, -2}
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