#pragma once
#include "CastlingCommand.h"

class CastlingCommandTest {
private:
	shared_ptr<Desk> desk;

	void DefaultCastlingTest();
	void CastlingWithFigureOnWayTest();
	void CastlingWhenCellsUnderAttackTest();
	void CastlingWhenOneOfTheFigureMoved();
	void CanselTest();

	void RenewDesk();

public:
	CastlingCommandTest();
};