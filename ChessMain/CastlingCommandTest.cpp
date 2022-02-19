#include "CastlingCommandTest.h"
#include <cassert>

CastlingCommandTest::CastlingCommandTest() {
	desk = make_shared<Desk>();

	DefaultCastlingTest();
	CastlingWhenCellsUnderAttackTest();
	CastlingWithFigureOnWayTest();
	CastlingWhenOneOfTheFigureMoved();
	CanselTest();
}

void CastlingCommandTest::DefaultCastlingTest() {
	RenewDesk();
	cout << "//////////////////////////////////////////////////" << endl;
	cout << "CastlingCommand test: default castling test" << endl;
	
	cout << "test on white king's flank" << endl;
	desk->Draw(); cout << endl; desk->CalculateAttackedCells();
	shared_ptr<Command> cmd1 = make_shared<CastlingCommand>(Flank::King, Color::White);
	assert(cmd1->Execute(desk) == true);
	desk->Draw(); cout << endl; desk->CalculateAttackedCells();

	RenewDesk();
	cout << "test on white queen's flank" << endl;
	desk->Draw(); cout << endl; desk->CalculateAttackedCells();
	shared_ptr<Command> cmd2 = make_shared<CastlingCommand>(Flank::Queen, Color::White);
	assert(cmd2->Execute(desk) == true);
	desk->Draw(); cout << endl; desk->CalculateAttackedCells();

	RenewDesk();
	cout << "test on black king's flank" << endl;
	desk->Draw(); cout << endl; desk->CalculateAttackedCells();
	shared_ptr<Command> cmd3 = make_shared<CastlingCommand>(Flank::King, Color::Black);
	assert(cmd3->Execute(desk) == true);
	desk->Draw(); cout << endl; desk->CalculateAttackedCells();

	RenewDesk();
	cout << "test on black queen's flank" << endl;
	desk->Draw(); cout << endl; desk->CalculateAttackedCells();
	shared_ptr<Command> cmd4 = make_shared<CastlingCommand>(Flank::Queen, Color::Black);
	assert(cmd4->Execute(desk) == true);

	desk->Draw(); cout << endl; desk->CalculateAttackedCells();
}

void CastlingCommandTest::CastlingWithFigureOnWayTest() {

}

void CastlingCommandTest::CastlingWhenCellsUnderAttackTest() {

}

void CastlingCommandTest::CastlingWhenOneOfTheFigureMoved() {

}

void CastlingCommandTest::CanselTest() {

}

void CastlingCommandTest::RenewDesk() {
	desk->DeleteAllFigures();
	desk->PlaceFigure(FigureType::King, Color::White, Coordinate(Horizontal::E, Vertical::One));
	desk->PlaceFigure(FigureType::Rook, Color::White, Coordinate(Horizontal::A, Vertical::One));
	desk->PlaceFigure(FigureType::Rook, Color::White, Coordinate(Horizontal::H, Vertical::One));

	desk->PlaceFigure(FigureType::King, Color::Black, Coordinate(Horizontal::E, Vertical::Eigth));
	desk->PlaceFigure(FigureType::Rook, Color::Black, Coordinate(Horizontal::A, Vertical::Eigth));
	desk->PlaceFigure(FigureType::Rook, Color::Black, Coordinate(Horizontal::H, Vertical::Eigth));
}