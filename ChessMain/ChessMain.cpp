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
#include "Command.h"
#include "MoveCommand.h"

using namespace std;

int main()
{
    shared_ptr<Desk> ds = make_shared<Desk>();
    ds->PlaceDefaultFigures();
    //ds.PlaceFigure(FigureType::King, Color::White, Coordinate(Horizontal::D, Vertical::Four));
    //ds.PlaceFigure(FigureType::King, Color::Black, Coordinate(Horizontal::E, Vertical::Two));
    //ds.PlaceFigure(FigureType::Rook, Color::Black, Coordinate(Horizontal::E, Vertical::One));
    //ds.PlaceFigure(FigureType::Rook, Color::Black, Coordinate(Horizontal::C, Vertical::One));
    shared_ptr<Command> cmd = make_shared<MoveCommand> (Coordinate(Horizontal::A, Vertical::Two), 
        Coordinate(Horizontal::A, Vertical::Four), 
        Color::White);

    ds->CalculateAttackedCells();
    /*auto cells = ds.GetAttackedCells(Color::Black);

    for (auto cell : cells) {
        cout << cell;
    }*/

    ds->Draw();

    cout << endl;

    cmd->Execute(ds);

    ds->Draw();

    cmd->Cansel(ds);
    ds->Draw();

    return 0;
}