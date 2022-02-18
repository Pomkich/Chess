#pragma once
#include "Command.h"
#include "Coordinate.h"

class MoveCommand : public Command {
private:
	Coordinate from;
	Coordinate to;

public:
	MoveCommand(Coordinate c_from, Coordinate c_to, Color c_col) : from(c_from), to(c_to) { color = c_col; };
	
	virtual bool Execute(std::shared_ptr<Desk> desk) override;
	virtual void Cansel(std::shared_ptr<Desk> desk) override {};
};