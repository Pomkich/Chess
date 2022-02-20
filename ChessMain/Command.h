#pragma once
#include "Desk.h"
#include <iostream>

class Command {
protected:
	Color color;
	bool executed;

	Coordinate move_coord;

public:
	virtual bool Execute(std::shared_ptr<Desk> desk) = 0;
	virtual bool Cansel(std::shared_ptr<Desk> desk) = 0;

	virtual Coordinate GetMovedFigureCoord() { if (executed) return move_coord; };
	Color GetColor() { return color; }
};