#include "CommandHolder.h"

CommandHolder::CommandHolder() {
	ready_to_send = false;
}

void CommandHolder::SetCommand(shared_ptr<Command> cmd) {
	unique_lock<mutex> lock(mut);
	hold_command = cmd;
	ready_to_send = true;
	lock.unlock();
	has_command.notify_one();
}

shared_ptr<Command> CommandHolder::GetCommand() {
	unique_lock<mutex> lock(mut);
	has_command.wait(lock, [&]() { return ready_to_send; });
	return hold_command;
}