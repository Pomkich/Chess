#pragma once
#include "Constants.h"
#include "Coordinate.h"

struct Cell {
	bool has_figure;
	Coordinate position;

	// if figure in cell
	Color color;
	FigureType type;

	Cell() {
		has_figure = false;
		position.hor = Horizontal::A;
		position.ver = Vertical::One;
		color = Color::White;
		type = FigureType::Pawn;
	}

	Cell(Horizontal new_hor, Vertical new_ver) {
		has_figure = false;
		position.hor = new_hor;
		position.ver = new_ver;
		color = Color::White;
		type = FigureType::Pawn;
	}
};