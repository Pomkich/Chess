﻿// ChessMain.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "MoveCommandTest.h"
#include "CastlingCommandTest.h"
#include "DeskViewerTest.h"

#include "Chess.h"

#include "SfmlControlManager.h"

using namespace std;

int main()
{
    //MoveCommandTest test1;
    //CastlingCommandTest test2;
    //DeskViewerTest test3;

    //Chess game;
    //game.StartNewGame();
    SfmlControlManager manager;


    return 0;
}

/*
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
    }

ds->Draw();

cout << endl;

cmd->Execute(ds);

ds->Draw();
cout << endl;
cmd->Cansel(ds);
ds->Draw();

*/