#pragma once
#include <iostream>
#include "Coordinate.h"
#include <list>

using namespace std;

class Figure {
protected:
	Color color;
	FigureType type;	// used for the convenience of rendering
	Coordinate current_pos;	// position of figure on board
	list<Coordinate> move_cells;	// the cells into which the figure can go
	list<pair<int, int>> move_vectors;	// used for implementing movement
	int move_range;

public:
	virtual void CalculateAttackedCells(const list<shared_ptr<Figure>> figures) = 0;	// defines move cells for this figure; takes all figures on desk
	list<Coordinate> GetMoveCells() { return move_cells; };

	void SetPosition(Coordinate pos) { current_pos = pos; }
	Coordinate GetPosition() { return current_pos; }

	void SetColor(Color col) { color = col; }
	Color GetColor() { return color; }

	FigureType GetType() { return type; }
};