#pragma once
#include "Figure.h"

class Bishop : public Figure {
public:
	Bishop() {
		type = FigureType::Bishop;
		color = Color::White;
		move_vectors = {
			{1, 1}, {-1, 1}, {1, -1}, {-1, -1}	// diagonal
		};
	}

	Bishop(Color col) {
		type = FigureType::Bishop;
		color = col;
		move_vectors = {
			{1, 1}, {-1, 1}, {1, -1}, {-1, -1}	// diagonal
		};
	}

	virtual void CalculateAttackedCells(const array<array<Cell, field_size>, field_size> desk) override {
		move_cells.clear();

		for (auto move_vec : move_vectors) {
			pair<int, int> coord = current_pos.ToInt();
			for (int i = 0; i < field_size; i++) {
				coord.first += move_vec.first;
				coord.second += move_vec.second;
				if (Coordinate::InBounds(coord.first, coord.second)) {
					if (!desk[coord.second][coord.first].has_figure ||
						(desk[coord.second][coord.first].figure_ptr->GetType() == FigureType::King &&
						desk[coord.second][coord.first].figure_ptr->GetColor() != color)) {
						move_cells.push_back(Coordinate((Horizontal)coord.first, (Vertical)coord.second));
					}
					else {
						if (desk[coord.second][coord.first].figure_ptr->GetColor() != color) {
							move_cells.push_back(Coordinate((Horizontal)coord.first, (Vertical)coord.second));
						}
						break;
					}					
				}
				else break;
			}
		}
	}
};