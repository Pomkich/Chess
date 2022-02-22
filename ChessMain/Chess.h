#pragma once

#include "Desk.h"
#include "DeskViewer.h"
#include "MoveCommand.h"
#include "CastlingCommand.h"
#include "ConsolePresenter.h"

class Chess {
private:
	Color player_turn;
	Color opposite_color;
	FinalState state;
	shared_ptr<Desk> desk;
	shared_ptr<DeskViewer> viewer;
	shared_ptr<Presenter> console_handler;
	int figures_on_desk;
	// shared_ptr<InputHandler> input;

public:
	Chess();
	void StartNewGame();
	void GameLoop();
	void PassTheMove();
};