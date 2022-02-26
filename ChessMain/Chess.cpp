#include "Chess.h"
#include <string>

using namespace std;

// code for input handler
shared_ptr<Command> GetCommand(Color color) {
	map<char, int> char_int = {
		{'a', 0},
		{'b', 1},
		{'c', 2},
		{'d', 3},
		{'e', 4},
		{'f', 5},
		{'g', 6},
		{'h', 7},
	};

	string str_cmd;
	cin >> str_cmd;

	shared_ptr<Command> cmd;

	if (str_cmd[0] == 'm') {
		int hor_from = char_int[str_cmd[1]];
		int ver_from = str_cmd[2] - '0' - 1;
		int hor_to = char_int[str_cmd[3]];
		int ver_to = str_cmd[4] - '0' - 1;
		cmd = make_shared<MoveCommand>(
			Coordinate((Horizontal)hor_from, (Vertical)ver_from),
			Coordinate((Horizontal)hor_to, (Vertical)ver_to), color);
	}
	else if (str_cmd[0] == 'O') {
		if (str_cmd[1] == 'O' && str_cmd[2] == 'O') {
			cmd = make_shared<CastlingCommand>(Flank::Queen, color);
		}
		else {
			cmd = make_shared<CastlingCommand>(Flank::King, color);
		}
	}

	return cmd;
}

Chess::Chess(shared_ptr<Desk> new_desk, weak_ptr<Presenter> new_presenter) {
	desk = new_desk;
	presenter = new_presenter;
	viewer = make_shared<DeskViewer>();
	viewer->SetDesk(desk);
	command_holder = make_shared<CommandHolder>();
	presenter.lock()->SetCommandHolder(command_holder);
	figures_on_desk = 0;
	player_turn = Color::White;
	opposite_color = Color::Black;
	state = FinalState::Undefined;
}

void Chess::StartNewGame() {
	desk->DeleteAllFigures();
	desk->PlaceDefaultFigures();
	figures_on_desk = 32;
	player_turn = Color::White;
	opposite_color = Color::Black;
	state = FinalState::Undefined;
	presenter.lock()->NotifyGameStarted();
	GameLoop();
}

void Chess::GameLoop() {
	while (state == FinalState::Undefined) {
		desk->Draw();
		desk->CalculateAttackedCells();
		cout << endl;

		cout << "player " << (int)player_turn << " turn: ";
		shared_ptr<Command> command;
		command = command_holder->GetCommand();
		// priority of events: game end, king shah, figure delete, figure moved
		if (viewer->CheckCommand(command)) {
			if (viewer->KingCheckmate(opposite_color, desk->GetFigure(command->GetMovedFigureCoord()))) {
				if (player_turn == Color::White) {
					state = FinalState::BlackCheckmated;
				}
				else {
					state = FinalState::WhiteCheckmated;
				}
			}
			else if (viewer->KingPat(opposite_color)) {
				state = FinalState::Pat;
			}
			else if (viewer->KingUnderAttack(opposite_color)) {
				presenter.lock()->NotifyKingShah(opposite_color);
			}
			if (desk->GetFigures(Color::Black).size() + desk->GetFigures(Color::White).size() != figures_on_desk) {
				figures_on_desk--;
				presenter.lock()->NotifyFigureDeleted(opposite_color);
			}
			else {
				presenter.lock()->NotifyFigureMoved();
			}
			PassTheMove();
		}
		else {
			presenter.lock()->NotifyBadCommand();
		}
	}

	presenter.lock()->NotifyGameEnd(state);

	switch (state) {
	case FinalState::WhiteCheckmated:
		cout << "black player won" << endl;
		break;

	case FinalState::BlackCheckmated:
		cout << "white player won" << endl;
		break;

	case FinalState::Pat:
		cout << "pat" << endl;
		break;
	}
}

void Chess::PassTheMove() {
	switch (player_turn) {
	case Color::White:
		player_turn = Color::Black;
		opposite_color = Color::White;
		break;

	case Color::Black:
		player_turn = Color::White;
		opposite_color = Color::Black;
		break;
	}
}
