#pragma once
#include "Desk.h"
#include <iostream>

class Command {
protected:
	Color color;
	bool executed;

public:
	virtual bool Execute(std::shared_ptr<Desk> desk) = 0;
	virtual void Cansel(std::shared_ptr<Desk> desk) = 0;
	Color GetColor() { return color; }
};