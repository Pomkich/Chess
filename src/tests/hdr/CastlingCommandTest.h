#pragma once
#include "CastlingCommand.h"
#include "MoveCommand.h"

class CastlingCommandTest {
private:
	shared_ptr<Desk> desk;

	void DefaultCastlingTest();
	void CastlingWithFigureOnWayTest();
	void CastlingWhenCellsUnderAttackTest();
	void CastlingWhenOneOfTheFigureMoved();

	void RenewDesk();

public:
	CastlingCommandTest();
};