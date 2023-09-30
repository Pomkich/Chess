#pragma once
#include "Desk.h"
#include "Constants.h"
#include "Command.h"
#include <iostream>

using namespace std;

// this class implements the rules of chess
class DeskViewer {
private: 
	shared_ptr<Desk> virtual_desk;	// this is a board for checking the ability to execute commands
	list<Coordinate> CalculateAttackVector(Coordinate attack_figure_pos, Coordinate king_pos);

public:
	DeskViewer();
	void SetDesk(shared_ptr<Desk> n_desk);
	bool CheckCommand(shared_ptr<Command> command);
	bool PawnReachedEnd(Coordinate coord);
	bool KingUnderAttack(Color color);
	bool KingCheckmate(Color color, shared_ptr<Figure> attacked_figure);
	bool KingPat(Color color);
};