#include "MoveCommandTest.h"
#include <cassert>

MoveCommandTest::MoveCommandTest() {
	desk = make_shared<Desk>();

	MoveInEmptyCellTest();
	MoveInOccupiedCellTest();
	MoveEnemyFigureTest();
	CanselTest();
}

void MoveCommandTest::MoveInEmptyCellTest() {
	RenewDesk();
	cout << "//////////////////////////////////////////////////" << endl;
	cout << "MoveCommand test: Moving figure in empty cell test" << endl;
	desk->PlaceFigure(FigureType::Rook, Color::White, Coordinate(Horizontal::D, Vertical::Four));
	desk->CalculateAttackedCells();

	cout << "moving to empty cell" << endl;
	desk->Draw(); cout << endl; desk->CalculateAttackedCells();
	shared_ptr<Command> cmd1 = make_shared<MoveCommand>(Coordinate(Horizontal::D, Vertical::Four), 
		Coordinate(Horizontal::D, Vertical::Six), Color::White);
	assert(cmd1->Execute(desk) == true);
	
	cout << "moving to empty cell" << endl;
	desk->Draw(); cout << endl; desk->CalculateAttackedCells();
	shared_ptr<Command> cmd2 = make_shared<MoveCommand>(Coordinate(Horizontal::D, Vertical::Six), 
		Coordinate(Horizontal::G, Vertical::Six), Color::White);
	assert(cmd2->Execute(desk) == true);

	cout << "trying to move in not attacked cell" << endl;
	desk->Draw(); cout << endl; desk->CalculateAttackedCells();
	shared_ptr<Command> cmd3 = make_shared<MoveCommand>(Coordinate(Horizontal::G, Vertical::Six), 
		Coordinate(Horizontal::A, Vertical::Three), Color::White);
	assert(cmd3->Execute(desk) == false);

	desk->Draw(); cout << endl;

}

void MoveCommandTest::MoveInOccupiedCellTest() {
	RenewDesk();
	cout << "//////////////////////////////////////////////////" << endl;
	cout << "MoveCommand test: Moving figure in occupied cell test" << endl;
	desk->PlaceFigure(FigureType::Queen, Color::White, Coordinate(Horizontal::B, Vertical::One));
	desk->PlaceFigure(FigureType::Horse, Color::Black, Coordinate(Horizontal::B, Vertical::Six));
	desk->PlaceFigure(FigureType::Bishop, Color::Black, Coordinate(Horizontal::C, Vertical::Five));
	desk->PlaceFigure(FigureType::Bishop, Color::White, Coordinate(Horizontal::H, Vertical::Five));
	
	cout << "attack enemy figure" << endl;
	desk->Draw(); cout << endl; desk->CalculateAttackedCells();
	shared_ptr<Command> cmd1 = make_shared<MoveCommand>(Coordinate(Horizontal::B, Vertical::One),
		Coordinate(Horizontal::B, Vertical::Six), Color::White);
	assert(cmd1->Execute(desk) == true);
	
	cout << "again attack enemy figure" << endl;
	desk->Draw(); cout << endl; desk->CalculateAttackedCells();
	shared_ptr<Command> cmd2 = make_shared<MoveCommand>(Coordinate(Horizontal::B, Vertical::Six),
		Coordinate(Horizontal::C, Vertical::Five), Color::White);
	assert(cmd2->Execute(desk) == true);
	
	cout << "trying to step occupied white cell" << endl;
	desk->Draw(); cout << endl; desk->CalculateAttackedCells();
	shared_ptr<Command> cmd3 = make_shared<MoveCommand>(Coordinate(Horizontal::C, Vertical::Five),
		Coordinate(Horizontal::H, Vertical::Five), Color::White);
	assert(cmd3->Execute(desk) == false);

	desk->Draw(); cout << endl;
}
void MoveCommandTest::MoveEnemyFigureTest() {
	RenewDesk();
	cout << "//////////////////////////////////////////////////" << endl;
	cout << "MoveCommand test: Moving enemy figure test" << endl;
	desk->PlaceFigure(FigureType::Queen, Color::White, Coordinate(Horizontal::B, Vertical::One));

	desk->Draw(); cout << endl; desk->CalculateAttackedCells();
	shared_ptr<Command> cmd1 = make_shared<MoveCommand>(Coordinate(Horizontal::B, Vertical::One),
		Coordinate(Horizontal::B, Vertical::Six), Color::Black);
	assert(cmd1->Execute(desk) == false);

	desk->Draw(); cout << endl;
}

void MoveCommandTest::CanselTest() {
	RenewDesk();
	cout << "//////////////////////////////////////////////////" << endl;
	cout << "MoveCommand test: Cansel command test" << endl;
	desk->PlaceFigure(FigureType::Queen, Color::White, Coordinate(Horizontal::B, Vertical::Three));

	cout << "cansel after execute" << endl;
	desk->Draw(); cout << endl; desk->CalculateAttackedCells();
	shared_ptr<Command> cmd1 = make_shared<MoveCommand>(Coordinate(Horizontal::B, Vertical::Three),
		Coordinate(Horizontal::B, Vertical::Six), Color::White);
	assert(cmd1->Execute(desk) == true);
	desk->Draw(); cout << endl; desk->CalculateAttackedCells();
	assert(cmd1->Cansel(desk) == true);
	desk->Draw(); cout << endl; desk->CalculateAttackedCells();

	cout << "cansel before execute" << endl;
	desk->Draw(); cout << endl; desk->CalculateAttackedCells();
	shared_ptr<Command> cmd2 = make_shared<MoveCommand>(Coordinate(Horizontal::B, Vertical::Three),
		Coordinate(Horizontal::B, Vertical::Six), Color::White);
	assert(cmd2->Cansel(desk) == false);
	desk->Draw(); cout << endl; desk->CalculateAttackedCells();
}

void MoveCommandTest::RenewDesk() {
	desk->DeleteAllFigures();
	desk->PlaceFigure(FigureType::King, Color::White, Coordinate(Horizontal::A, Vertical::One));
	desk->PlaceFigure(FigureType::King, Color::Black, Coordinate(Horizontal::H, Vertical::Eigth));
}