#pragma once
#include "Constants.h"
#include <iostream>

class Coordinate {
private:
	Horizontal hor;
	Vertical ver;

public:
	Coordinate() : hor(Horizontal::A), ver(Vertical::One) {};
	Coordinate(Horizontal new_hor, Vertical new_ver) : hor(new_hor), ver(new_ver) {};

	static bool Compare(const Coordinate& c1, const Coordinate& c2) {
		return (c1.hor == c2.hor && c1.ver == c2.ver) ? true : false;
	}

	friend std::ostream& operator<<(std::ostream& os, const Coordinate& coord) {
		return os << static_cast<int>(coord.hor) << ":" << static_cast<int>(coord.ver) << std::endl;
	}
};