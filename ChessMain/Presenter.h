#pragma once
#include "Constants.h"
#include "CommandHolder.h"

class Presenter {
protected:
	shared_ptr<CommandHolder> command_holder;
public:
	virtual void SetCommandHolder(shared_ptr<CommandHolder> cmd_hld) { command_holder = cmd_hld; }

	virtual void NotifyGameStarted() = 0;
	virtual void NotifyKingShah(Color oposite_color) = 0;
	virtual void NotifyGameEnd(FinalState state) = 0;
	virtual void NotifyFigureMoved() = 0;
	virtual void NotifyFigureDeleted() = 0;
};

