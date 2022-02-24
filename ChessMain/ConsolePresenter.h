#pragma once
#include "Presenter.h"
#include <iostream>

using namespace std;

class ConsolePresenter : public Presenter {
public:
	ConsolePresenter();
	virtual void NotifyGameStarted() override;
	virtual void NotifyKingShah(Color oposite_color) override;
	virtual void NotifyGameEnd(FinalState state) override;
	virtual void NotifyFigureMoved() override;
	virtual void NotifyFigureDeleted() override;
};