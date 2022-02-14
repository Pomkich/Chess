#pragma once
#include <iostream>
#include <array>
#include <list>
#include <set>
#include "Coordinate.h"
#include "Figure.h"
#include "Pawn.h"
#include "Rook.h"
#include "Horse.h"
#include "Bishop.h"
#include "King.h"
#include "Queen.h"
#include "Cell.h"

using namespace std;

class Desk {
private:
	array<array<Cell, field_size>, field_size> field;	// cells of game field
	list<shared_ptr<Figure>> figures[2];	// figures of each player
	set<Coordinate> attacked_cells[2];	// one coordinate can't be duplicated, so set is used

public:
	Desk();
	void CalculateAttackedCells();
	set<Coordinate> GetAttackedCells(Color col);
	void PlaceFigure(FigureType type, Color color, Coordinate pos);
	shared_ptr<Figure> GetFigure(const Coordinate figure_pos);
	void Draw();
};