#pragma once
#include "Command.h"
#include "Constants.h"

class CastlingCommand : public Command {
private:
	Flank flank;	// Queen's or King's flank

public:
	CastlingCommand(Flank c_flank, Color c_col) : flank(c_flank) { color = c_col; };

	virtual bool Execute(std::shared_ptr<Desk> desk) override {};
	virtual void Cansel(std::shared_ptr<Desk> desk) override {};
};