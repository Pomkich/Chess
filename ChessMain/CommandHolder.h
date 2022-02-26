#pragma once
#include "Command.h"
#include <mutex>

class CommandHolder {
private:
	shared_ptr<Command> hold_command;
	condition_variable has_command;
	mutex mut;

	bool ready_to_send;

public:
	CommandHolder();
	void SetCommand(shared_ptr<Command> cmd);
	shared_ptr<Command> GetCommand();
};