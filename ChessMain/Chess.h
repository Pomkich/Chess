#pragma once

#include "Desk.h"
#include "DeskViewer.h"
#include "MoveCommand.h"
#include "CastlingCommand.h"
#include "ConsolePresenter.h"
#include "CommandHolder.h"

class Chess {
private:
	Color player_turn;
	Color opposite_color;
	FinalState state;
	shared_ptr<Desk> desk;
	shared_ptr<DeskViewer> viewer;
	weak_ptr<Presenter> presenter;
	int figures_on_desk;
	shared_ptr<CommandHolder> command_holder;

public:
	Chess(shared_ptr<Desk> new_desk, weak_ptr<Presenter> new_presenter);
	void StartNewGame();
	void GameLoop();
	void PassTheMove();
};