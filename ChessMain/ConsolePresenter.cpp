#include "ConsolePresenter.h"

ConsolePresenter::ConsolePresenter() {}

void ConsolePresenter::NotifyKingShah(Color oposite_color) {
	cout << "king " << (int)oposite_color << " shahed" << endl;
}

void ConsolePresenter::NotifyGameEnd(FinalState state) {
	cout << "game end with state " << (int)state << endl;
}

void ConsolePresenter::NotifyFigureMoved() {
	cout << "figure moved" << endl;
}

void ConsolePresenter::NotifyFigureDeleted() {
	cout << "figure deleted" << endl;
}