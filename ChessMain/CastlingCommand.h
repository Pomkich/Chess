#pragma once
#include "Command.h"
#include "Constants.h"

class CastlingCommand : public Command {
	friend class CastlingCommandTest;

private:
	Flank flank;	// Queen's or King's flank

	Coordinate king_from, king_to;	// needed for cansel
	Coordinate rook_from, rook_to;

	tuple<shared_ptr<Figure>, shared_ptr<Figure>, list<shared_ptr<Figure>>> TryGetFigures(std::shared_ptr<Desk> desk);
	bool CellsIsAttacked(std::shared_ptr<Desk> desk);

public:
	CastlingCommand(Flank c_flank, Color c_col) : flank(c_flank) { color = c_col; executed = false; };

	virtual bool Execute(std::shared_ptr<Desk> desk) override;
	virtual bool Cansel(std::shared_ptr<Desk> desk) override;
};