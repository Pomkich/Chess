#pragma once
#include "Command.h"
#include "Coordinate.h"

class MoveCommand : public Command {
	friend class MoveCommandTest;
private:
	Coordinate from;
	Coordinate to;

	bool delete_figure;
	bool figure_first_move;
	FigureType deleted_figure_type;

public:
	MoveCommand(Coordinate c_from, Coordinate c_to, Color c_col) : from(c_from), to(c_to) { 
		color = c_col; 
		delete_figure = false;
		executed = false;
		figure_first_move = false;
	};
	
	virtual bool Execute(std::shared_ptr<Desk> desk) override;
	virtual bool Cansel(std::shared_ptr<Desk> desk) override;
};