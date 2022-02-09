// ChessMain.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "Constants.h"
#include "Coordinate.h"
#include "Desk.h"

using namespace std;

int main()
{
    Desk desk;
    desk.CalculateAttackedCells(Color::White);
    desk.Draw();
    desk.GetAttackedCells(Color::Black);

    return 1;
}