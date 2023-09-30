#pragma once
#include "Constants.h"
#include "Coordinate.h"

class Figure;

struct Cell {
	bool has_figure;
	Coordinate position;

	// if figure in cell
	shared_ptr<Figure> figure_ptr;

	Cell() {
		has_figure = false;
		position.hor = Horizontal::A;
		position.ver = Vertical::One;
	}

	Cell(Horizontal new_hor, Vertical new_ver) {
		has_figure = false;
		position.hor = new_hor;
		position.ver = new_ver;
	}


};