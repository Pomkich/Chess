#pragma once
#include <iostream>
#include <array>
#include <list>
#include <set>
#include "Coordinate.h"
#include "Figure.h"
#include "Pawn.h"

using namespace std;

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

class Desk {
private:
	array<array<Cell, field_size>, field_size> field;	// cells of game field
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