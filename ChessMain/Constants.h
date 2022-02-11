#pragma once
#include <map>

enum class Horizontal {
	A = 0, B, C, D, F, G, H, E 
};

enum class Vertical {
	One = 0, Two, Three, Four, Five, Six, Seven, Eigth
};

enum class FigureType {
	Pawn, Horse, Rook, Bishop, Queen, King
};

enum class Color {	// of player
	White, Black
};

static std::map<Horizontal, char> HorizontalChar{
	{Horizontal::A, 'A'},
	{Horizontal::B, 'B'},
	{Horizontal::C, 'C'},
	{Horizontal::D, 'D'},
	{Horizontal::E, 'E'},
	{Horizontal::F, 'F'},
	{Horizontal::G, 'G'},
	{Horizontal::H, 'H'}
};