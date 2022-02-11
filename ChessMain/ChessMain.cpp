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
    ds.Draw();

    shared_ptr<Figure> ptr1 = make_shared<Horse>();
    shared_ptr<Figure> ptr2 = make_shared<King>();
    shared_ptr<Figure> ptr3 = make_shared<Queen>();
    shared_ptr<Figure> ptr4 = make_shared<Rook>();
    shared_ptr<Figure> ptr5 = make_shared<Bishop>();

    return 0;
}