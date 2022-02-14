// ChessMain.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "Constants.h"
#include "Coordinate.h"
#include "Desk.h"
#include "Pawn.h"
#include "Horse.h"
#include "Bishop.h"
#include "King.h"
#include "Queen.h"
#include "Rook.h"

using namespace std;

int main()
{
    Desk ds;
    ds.PlaceDefaultFigures();

    ds.MoveFigure(Coordinate(Horizontal::A, Vertical::Two), Coordinate(Horizontal::A, Vertical::Four));
    ds.MoveFigure(Coordinate(Horizontal::C, Vertical::Two), Coordinate(Horizontal::C, Vertical::Eigth));
    ds.MoveFigure(Coordinate(Horizontal::B, Vertical::Two), Coordinate(Horizontal::C, Vertical::Four));

    ds.CalculateAttackedCells();
    auto cells = ds.GetAttackedCells(Color::White);

    for (auto cell : cells) {
        cout << cell;
    }

    ds.Draw();

    return 0;
}