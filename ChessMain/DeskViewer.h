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

public:
	// maybe should take command with pointer
	// the method of checking the command, if it is successful, then the command is executed on a real desk
	bool CheckCommand(Command command, Color color) {
		/* pveudo code
	if (command->Execute(this) != Command::BadCommand) {
		if (!KingUnderAttack(color)) {
			return true;
		}
		else {
			command->Cansel(this);
			return false;
		}
	}

	*/
	}
	// search for the check
	bool KingUnderAttack(Color color) {

	}
	// search for checkmate
	bool KingCheckmate(Color color) {

	};
	// search for pat
	bool KingPat(Color color) {

	};

};