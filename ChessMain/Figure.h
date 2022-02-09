#pragma once
#include <iostream>
#include "Coordinate.h"
#include <list>

using namespace std;

class Figure {
private:
	Coordinate current_pos;	// position of figure on board
	list<Coordinate> move_cells;	// the cells into which the figure can go
	list<pair<int, int>> move_vectors;	// used for implementing movement
	int move_range;

public:
	virtual void CalculateCells(list<Coordinate> figure_positions) = 0;	// defines move cells for this figure
	list<Coordinate> GetMoveCells() { return move_cells; };
	void SetPosition(Coordinate pos) { current_pos = pos; }
	Coordinate GetPosition() { return current_pos; }
};