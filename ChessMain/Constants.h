#pragma once
#include <map>

static const int field_size = 8;

enum class Horizontal {
	A = 0, B, C, D, E, F, G, H 
};

enum class Vertical {
	One = 0, Two, Three, Four, Five, Six, Seven, Eigth
};

enum class FigureType {
	Pawn, Rook, Horse, Bishop, Queen, King
};

enum class Color {	// of player
	White, Black
};

enum class Flank {
	Queen, King
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