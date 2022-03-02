#pragma once
#include <iostream>
#include "Coordinate.h"
#include "Cell.h"
#include <list>

using namespace std;

class Figure {
protected:
	bool walked;
	Color color;
	FigureType type;	// used for the convenience of rendering
	Coordinate current_pos;	// position of figure on board
	list<Coordinate> move_cells;	// the cells into which the figure can go
	list<Coordinate> attack_cells;
	list<pair<int, int>> move_vectors;	// used for implementing movement

public:
	virtual void CalculateAttackedCells(const array<array<Cell, field_size>, field_size> desk) = 0;	// defines move cells for this figure; takes all figures on desk
	list<Coordinate> GetMoveCells() { return move_cells; };
	list<Coordinate> GetAttackCells() { return attack_cells; }
	void RemoveMoveCell(Coordinate coord) { move_cells.remove(coord); };
	void RemoveAttackCell(Coordinate coord) { attack_cells.remove(coord); };

	void SetPosition(Coordinate pos) { current_pos = pos; }
	Coordinate GetPosition() { return current_pos; }

	void SetColor(Color col) { color = col; }
	Color GetColor() { return color; }

	FigureType GetType() { return type; }

	void SetWalked(bool st) { walked = st; }
	bool IsWalked() { return walked; }

	~Figure() {
		cout << "destructor called" << endl;
	}
};