#include "DeskViewerTest.h"

DeskViewerTest::DeskViewerTest() {
	desk = make_shared<Desk>();
	viewer = make_shared<DeskViewer>();

	CheckCommandTest();
	KingUnderAttackTest();
	KingCheckmateTest();
	KingPatTest();
}

void DeskViewerTest::CheckCommandTest() {
	RenewDesk();
	cout << "//////////////////////////////////////////////////" << endl;
	cout << "DeskViewerTest: check command test" << endl;

	cout << "when king would be attacked after executing command" << endl;
	desk->PlaceFigure(FigureType::Bishop, Color::Black, Coordinate(Horizontal::A, Vertical::Five));
	desk->PlaceFigure(FigureType::Pawn, Color::White, Coordinate(Horizontal::D, Vertical::Two));
	shared_ptr<Command> mv1 = make_shared<MoveCommand> (Coordinate(Horizontal::D, Vertical::Two),
			Coordinate(Horizontal::D, Vertical::Three), Color::White);
	desk->Draw(); cout << endl; desk->CalculateAttackedCells();
	assert(viewer->CheckCommand(mv1) == false);
	desk->Draw(); cout << endl; desk->CalculateAttackedCells();

	RenewDesk();
	cout << "when command is executable" << endl;
	desk->PlaceFigure(FigureType::Bishop, Color::Black, Coordinate(Horizontal::A, Vertical::Four));
	desk->PlaceFigure(FigureType::Pawn, Color::White, Coordinate(Horizontal::D, Vertical::Two));
	shared_ptr<Command> mv2 = make_shared<MoveCommand>(Coordinate(Horizontal::D, Vertical::Two),
		Coordinate(Horizontal::D, Vertical::Three), Color::White);
	desk->Draw(); cout << endl; desk->CalculateAttackedCells();
	assert(viewer->CheckCommand(mv2) == true);
	desk->Draw(); cout << endl; desk->CalculateAttackedCells();
}

void DeskViewerTest::KingUnderAttackTest() {
	cout << "King under attack test" << endl;
	
	RenewDesk();
	cout << "king under attack" << endl;
	desk->PlaceFigure(FigureType::Rook, Color::Black, Coordinate(Horizontal::E, Vertical::Five));
	desk->PlaceFigure(FigureType::Pawn, Color::White, Coordinate(Horizontal::D, Vertical::Two));
	desk->Draw(); cout << endl; desk->CalculateAttackedCells();
	assert(viewer->KingUnderAttack(Color::White) == true);
	
	RenewDesk();
	cout << "king not under attack" << endl;
	desk->PlaceFigure(FigureType::Rook, Color::Black, Coordinate(Horizontal::E, Vertical::Five));
	desk->PlaceFigure(FigureType::Pawn, Color::White, Coordinate(Horizontal::E, Vertical::Two));
	desk->Draw(); cout << endl; desk->CalculateAttackedCells();
	assert(viewer->KingUnderAttack(Color::White) == false);
}

void DeskViewerTest::KingCheckmateTest() {
	cout << "king checkmate test" << endl;

	cout << "king checkmated" << endl;
	RenewDesk();
	desk->PlaceFigure(FigureType::Rook, Color::Black, Coordinate(Horizontal::A, Vertical::One));
	desk->PlaceFigure(FigureType::Rook, Color::Black, Coordinate(Horizontal::B, Vertical::Two));
	desk->Draw(); cout << endl; desk->CalculateAttackedCells();
	auto figure1 = desk->GetFigure(Coordinate(Horizontal::A, Vertical::One));
	assert(viewer->KingCheckmate(Color::White, figure1) == true);

	cout << "king not checkmated: can kill attacking figure" << endl;
	RenewDesk();
	desk->PlaceFigure(FigureType::Queen, Color::Black, Coordinate(Horizontal::D, Vertical::Two));
	desk->Draw(); cout << endl; desk->CalculateAttackedCells();
	auto figure2 = desk->GetFigure(Coordinate(Horizontal::D, Vertical::Two));
	assert(viewer->KingCheckmate(Color::White, figure2) == false);

	cout << "king not checkmated: can block attacking vector" << endl;
	RenewDesk();
	desk->PlaceFigure(FigureType::Rook, Color::Black, Coordinate(Horizontal::A, Vertical::Seven));
	desk->PlaceFigure(FigureType::Bishop, Color::Black, Coordinate(Horizontal::B, Vertical::Four));
	desk->PlaceFigure(FigureType::Rook, Color::White, Coordinate(Horizontal::D, Vertical::One));
	desk->PlaceFigure(FigureType::Rook, Color::White, Coordinate(Horizontal::F, Vertical::One));
	desk->Draw(); cout << endl; desk->CalculateAttackedCells();
	auto figure3 = desk->GetFigure(Coordinate(Horizontal::B, Vertical::Four));
	assert(viewer->KingCheckmate(Color::White, figure3) == false);

	cout << "king not checkmated: can run away from attacking vector" << endl;
	RenewDesk();
	desk->PlaceFigure(FigureType::Queen, Color::Black, Coordinate(Horizontal::C, Vertical::Three));
	desk->Draw(); cout << endl; desk->CalculateAttackedCells();
	auto figure4 = desk->GetFigure(Coordinate(Horizontal::C, Vertical::Three));
	assert(viewer->KingCheckmate(Color::White, figure4) == false);

	cout << "king checkmated: baby mat" << endl;
	desk->DeleteAllFigures();
	desk->PlaceDefaultFigures();
	desk->MoveFigure(Coordinate(Horizontal::E, Vertical::Two), Coordinate(Horizontal::E, Vertical::Four));
	desk->MoveFigure(Coordinate(Horizontal::E, Vertical::Seven), Coordinate(Horizontal::E, Vertical::Five));
	desk->MoveFigure(Coordinate(Horizontal::B, Vertical::Eigth), Coordinate(Horizontal::A, Vertical::Six));
	desk->MoveFigure(Coordinate(Horizontal::D, Vertical::Seven), Coordinate(Horizontal::D, Vertical::Four));
	desk->MoveFigure(Coordinate(Horizontal::D, Vertical::One), Coordinate(Horizontal::H, Vertical::Five));
	desk->MoveFigure(Coordinate(Horizontal::F, Vertical::One), Coordinate(Horizontal::C, Vertical::Four));

	desk->Draw(); cout << endl; desk->CalculateAttackedCells();
	shared_ptr<Command> mv1 = make_shared<MoveCommand>(Coordinate(Horizontal::H, Vertical::Five),
		Coordinate(Horizontal::F, Vertical::Seven), Color::White);
	mv1->Execute(desk);
	desk->Draw(); cout << endl; desk->CalculateAttackedCells();
	auto figure5 = desk->GetFigure(Coordinate(Horizontal::F, Vertical::Seven));
	assert(viewer->KingCheckmate(Color::Black, figure5) == true);
}

void DeskViewerTest::KingPatTest() {
	cout << "king pat test" << endl;

	RenewDesk();
	desk->PlaceFigure(FigureType::Rook, Color::Black, Coordinate(Horizontal::A, Vertical::Two));
	desk->PlaceFigure(FigureType::Rook, Color::Black, Coordinate(Horizontal::F, Vertical::Five));
	desk->PlaceFigure(FigureType::Queen, Color::Black, Coordinate(Horizontal::D, Vertical::Five));
	desk->Draw(); cout << endl; desk->CalculateAttackedCells();
	assert(viewer->KingPat(Color::White) == true);

	RenewDesk();
	desk->PlaceFigure(FigureType::Rook, Color::Black, Coordinate(Horizontal::D, Vertical::Two));
	desk->PlaceFigure(FigureType::Rook, Color::Black, Coordinate(Horizontal::F, Vertical::Two));
	desk->Draw(); cout << endl; desk->CalculateAttackedCells();
	assert(viewer->KingPat(Color::White) == true);

	RenewDesk();
	desk->PlaceFigure(FigureType::Rook, Color::Black, Coordinate(Horizontal::D, Vertical::Two));
	desk->PlaceFigure(FigureType::Rook, Color::Black, Coordinate(Horizontal::F, Vertical::Two));
	desk->PlaceFigure(FigureType::Pawn, Color::Black, Coordinate(Horizontal::A, Vertical::Five));
	desk->PlaceFigure(FigureType::Pawn, Color::Black, Coordinate(Horizontal::B, Vertical::Four));
	desk->PlaceFigure(FigureType::Pawn, Color::White, Coordinate(Horizontal::A, Vertical::Four));
	desk->PlaceFigure(FigureType::Pawn, Color::White, Coordinate(Horizontal::B, Vertical::Three));
	desk->Draw(); cout << endl; desk->CalculateAttackedCells();
	assert(viewer->KingPat(Color::White) == true);

	RenewDesk();
	desk->PlaceFigure(FigureType::Horse, Color::Black, Coordinate(Horizontal::D, Vertical::Two));
	desk->PlaceFigure(FigureType::Horse, Color::Black, Coordinate(Horizontal::F, Vertical::Two));
	desk->PlaceFigure(FigureType::Pawn, Color::Black, Coordinate(Horizontal::A, Vertical::Five));
	desk->PlaceFigure(FigureType::Pawn, Color::Black, Coordinate(Horizontal::B, Vertical::Four));
	desk->PlaceFigure(FigureType::Pawn, Color::White, Coordinate(Horizontal::A, Vertical::Four));
	desk->PlaceFigure(FigureType::Pawn, Color::White, Coordinate(Horizontal::B, Vertical::Three));
	desk->MoveFigure(Coordinate(Horizontal::E, Vertical::Eigth), Coordinate(Horizontal::E, Vertical::Three));
	desk->Draw(); cout << endl; desk->CalculateAttackedCells();
	assert(viewer->KingPat(Color::White) == true);

	RenewDesk();
	desk->PlaceFigure(FigureType::Horse, Color::Black, Coordinate(Horizontal::D, Vertical::Two));
	desk->PlaceFigure(FigureType::Horse, Color::White, Coordinate(Horizontal::F, Vertical::Two));
	desk->PlaceFigure(FigureType::Pawn, Color::Black, Coordinate(Horizontal::A, Vertical::Five));
	desk->PlaceFigure(FigureType::Pawn, Color::Black, Coordinate(Horizontal::B, Vertical::Four));
	desk->PlaceFigure(FigureType::Pawn, Color::White, Coordinate(Horizontal::A, Vertical::Four));
	desk->PlaceFigure(FigureType::Pawn, Color::White, Coordinate(Horizontal::B, Vertical::Three));
	desk->MoveFigure(Coordinate(Horizontal::E, Vertical::Eigth), Coordinate(Horizontal::E, Vertical::Three));
	desk->Draw(); cout << endl; desk->CalculateAttackedCells();
	assert(viewer->KingPat(Color::White) == false);
}

void DeskViewerTest::RenewDesk() {
	desk->DeleteAllFigures();
	desk->PlaceFigure(FigureType::King, Color::White, Coordinate(Horizontal::E, Vertical::One));
	desk->PlaceFigure(FigureType::King, Color::Black, Coordinate(Horizontal::E, Vertical::Eigth));
	viewer->SetDesk(desk);
}