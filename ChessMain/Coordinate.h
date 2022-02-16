#pragma once
#include "Constants.h"
#include <iostream>

using namespace std;

class Coordinate {
public:
	Horizontal hor;
	Vertical ver;
	
	Coordinate() : hor(Horizontal::A), ver(Vertical::One) {};
	Coordinate(Horizontal new_hor, Vertical new_ver) : hor(new_hor), ver(new_ver) {};

	static bool Compare(const Coordinate& c1, const Coordinate& c2) {
		return (c1.hor == c2.hor && c1.ver == c2.ver) ? true : false;
	}
	
	static bool InBounds(int hor, int ver) { return ((hor >= 0 && hor <= 7) && (ver >= 0 && ver <= 7)); }

	pair<int, int> ToInt() { return make_pair((int)hor, (int)ver); };

	friend std::ostream& operator<<(std::ostream& os, const Coordinate& coord) {
		return os << HorizontalChar[coord.hor] << ":" << static_cast<int>(coord.ver) + 1 << std::endl;
	}

	friend bool operator==(const Coordinate& c1, const Coordinate& c2) {
		return (c1.hor == c2.hor && c1.ver == c2.ver) ? true : false;
	}

	friend bool operator<(const Coordinate& c1, const Coordinate& c2) {
		// can do with a coefficient showing the importance of the horizontal, in this case the ten is taken as the coefficient
		return (((int)c1.hor * 10 + (int)c1.ver) < ((int)c2.hor * 10 + (int)c2.ver));
	}	// need's to be optimized ofc
};
