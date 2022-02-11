#pragma once
#include <iostream>
#include <array>
#include <list>
#include <set>
#include "Coordinate.h"
#include "Figure.h"
#include "Pawn.h"

using namespace std;

class Desk {
private:
	array<array<int, 8>, 8> field;	// cells of game field
	list<shared_ptr<Figure>> figures[2];	// figures of each player
	set<Coordinate> attacked_cells[2];	// one coordinate can't be duplicated, so set is used

public:
	Desk();
	void CalculateAttackedCells(Color col);
	set<Coordinate> GetAttackedCells(Color col);
	unique_ptr<Figure> GetFigure(const Coordinate figure_pos);
	list<unique_ptr<Figure>> GetFigures(Color col);	// probably need to pass by value
	void Draw();
};