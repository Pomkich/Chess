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
    
    ds.PlaceFigure(FigureType::King, Color::White, Coordinate(Horizontal::D, Vertical::Four));
    ds.PlaceFigure(FigureType::King, Color::Black, Coordinate(Horizontal::E, Vertical::Two));
    //ds.PlaceFigure(FigureType::Rook, Color::Black, Coordinate(Horizontal::E, Vertical::One));
    //ds.PlaceFigure(FigureType::Rook, Color::Black, Coordinate(Horizontal::C, Vertical::One));

    ds.CalculateAttackedCells();
    auto cells = ds.GetAttackedCells(Color::Black);

    for (auto cell : cells) {
        cout << cell;
    }

    ds.Draw();

    return 0;
}