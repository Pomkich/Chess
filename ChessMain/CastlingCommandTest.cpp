#include "CastlingCommandTest.h"
#include <cassert>

CastlingCommandTest::CastlingCommandTest() {
	desk = make_shared<Desk>();

	DefaultCastlingTest();
	CastlingWithFigureOnWayTest();
	CastlingWhenCellsUnderAttackTest();
	CastlingWhenOneOfTheFigureMoved();
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
	RenewDesk();
	cout << "//////////////////////////////////////////////////" << endl;
	cout << "CastlingCommand test: figure on way of castling test" << endl;

	cout << "king white test" << endl;
	desk->PlaceFigure(FigureType::Bishop, Color::White, Coordinate(Horizontal::F, Vertical::One));
	desk->Draw(); cout << endl; desk->CalculateAttackedCells();
	shared_ptr<Command> cmd1 = make_shared<CastlingCommand>(Flank::King, Color::White);
	assert(cmd1->Execute(desk) == false);
	desk->Draw(); cout << endl; desk->CalculateAttackedCells();

	RenewDesk();
	cout << "queen white test" << endl;
	desk->PlaceFigure(FigureType::Bishop, Color::White, Coordinate(Horizontal::C, Vertical::One));
	desk->Draw(); cout << endl; desk->CalculateAttackedCells();
	shared_ptr<Command> cmd2 = make_shared<CastlingCommand>(Flank::Queen, Color::White);
	assert(cmd2->Execute(desk) == false);
	desk->Draw(); cout << endl; desk->CalculateAttackedCells();

	RenewDesk();
	cout << "king black test" << endl;
	desk->PlaceFigure(FigureType::Bishop, Color::Black, Coordinate(Horizontal::F, Vertical::Eigth));
	desk->Draw(); cout << endl; desk->CalculateAttackedCells();
	shared_ptr<Command> cmd3 = make_shared<CastlingCommand>(Flank::King, Color::Black);
	assert(cmd3->Execute(desk) == false);
	desk->Draw(); cout << endl; desk->CalculateAttackedCells();

	RenewDesk();
	cout << "queen black test" << endl;
	desk->PlaceFigure(FigureType::Bishop, Color::Black, Coordinate(Horizontal::C, Vertical::Eigth));
	desk->Draw(); cout << endl; desk->CalculateAttackedCells();
	shared_ptr<Command> cmd4 = make_shared<CastlingCommand>(Flank::Queen, Color::Black);
	assert(cmd4->Execute(desk) == false);
	desk->Draw(); cout << endl; desk->CalculateAttackedCells();

}

void CastlingCommandTest::CastlingWhenCellsUnderAttackTest() {
	RenewDesk();
	cout << "//////////////////////////////////////////////////" << endl;
	cout << "CastlingCommand test: cell attacked on way of castling" << endl;

	cout << "king white test" << endl;
	desk->PlaceFigure(FigureType::Bishop, Color::Black, Coordinate(Horizontal::H, Vertical::Three));
	desk->Draw(); cout << endl; desk->CalculateAttackedCells();
	shared_ptr<Command> cmd1 = make_shared<CastlingCommand>(Flank::King, Color::White);
	assert(cmd1->Execute(desk) == false);
	desk->Draw(); cout << endl; desk->CalculateAttackedCells();

	RenewDesk();
	cout << "queen white test" << endl;
	desk->PlaceFigure(FigureType::Bishop, Color::Black, Coordinate(Horizontal::A, Vertical::Three));
	desk->Draw(); cout << endl; desk->CalculateAttackedCells();
	shared_ptr<Command> cmd2 = make_shared<CastlingCommand>(Flank::Queen, Color::White);
	assert(cmd2->Execute(desk) == false);
	desk->Draw(); cout << endl; desk->CalculateAttackedCells();

	RenewDesk();
	cout << "king black test" << endl;
	desk->PlaceFigure(FigureType::Bishop, Color::White, Coordinate(Horizontal::H, Vertical::Six));
	desk->Draw(); cout << endl; desk->CalculateAttackedCells();
	shared_ptr<Command> cmd3 = make_shared<CastlingCommand>(Flank::King, Color::Black);
	assert(cmd3->Execute(desk) == false);
	desk->Draw(); cout << endl; desk->CalculateAttackedCells();

	RenewDesk();
	cout << "queen black test" << endl;
	desk->PlaceFigure(FigureType::Bishop, Color::White, Coordinate(Horizontal::A, Vertical::Six));
	desk->Draw(); cout << endl; desk->CalculateAttackedCells();
	shared_ptr<Command> cmd4 = make_shared<CastlingCommand>(Flank::Queen, Color::Black);
	assert(cmd4->Execute(desk) == false);
	desk->Draw(); cout << endl; desk->CalculateAttackedCells();
}

void CastlingCommandTest::CastlingWhenOneOfTheFigureMoved() {
	RenewDesk();
	cout << "//////////////////////////////////////////////////" << endl;
	cout << "CastlingCommand test: one of castling figure moved" << endl;

	desk->Draw(); cout << endl; desk->CalculateAttackedCells();
	shared_ptr<Command> cmdm1 = make_shared<MoveCommand>(Coordinate(Horizontal::E, Vertical::One), 
		Coordinate(Horizontal::E, Vertical::Two), Color::White);
	shared_ptr<Command> cmdm2 = make_shared<MoveCommand>(Coordinate(Horizontal::E, Vertical::Two), 
		Coordinate(Horizontal::E, Vertical::One), Color::White);
	cmdm1->Execute(desk);
	desk->Draw(); cout << endl; desk->CalculateAttackedCells();
	cmdm2->Execute(desk);
	desk->Draw(); cout << endl; desk->CalculateAttackedCells();
	shared_ptr<Command> cmd1 = make_shared<CastlingCommand>(Flank::King, Color::White);
	assert(cmd1->Execute(desk) == false);
	desk->Draw(); cout << endl; desk->CalculateAttackedCells();
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