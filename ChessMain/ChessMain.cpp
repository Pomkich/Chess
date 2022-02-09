// ChessMain.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "Constants.h"
#include "Coordinate.h"
#include "Desk.h"
#include "Pawn.h"

using namespace std;

int main()
{
    unique_ptr<Figure> pawn1 = make_unique<Pawn>(Color::White);

    return 0;
}