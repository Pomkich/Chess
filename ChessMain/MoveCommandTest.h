#pragma once
#include "MoveCommand.h"

class MoveCommandTest {
private:
	shared_ptr<Desk> desk;

	void MoveInEmptyCellTest();
	void MoveInOccupiedCellTest();
	void MoveEnemyFigureTest();
	void CanselTest();

	void RenewDesk();

public:
	MoveCommandTest();
};