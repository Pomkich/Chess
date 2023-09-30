#pragma once

#include "DeskViewer.h" 
#include "MoveCommand.h"
#include <cassert>

class DeskViewerTest {
private:
	shared_ptr<Desk> desk;
	shared_ptr<DeskViewer> viewer;


	void CheckCommandTest();
	void KingUnderAttackTest();
	void KingCheckmateTest();
	void KingPatTest();

	void RenewDesk();

public:
	DeskViewerTest();
};