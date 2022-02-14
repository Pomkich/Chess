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
    ds.CalculateAttackedCells();
    ds.Draw();

    return 0;
}