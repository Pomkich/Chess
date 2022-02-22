#pragma once
#include "Constants.h"

class Presenter {
public:
	virtual void NotifyKingShah(Color oposite_color) = 0;
	virtual void NotifyGameEnd(FinalState state) = 0;
	virtual void NotifyFigureMoved() = 0;
	virtual void NotifyFigureDeleted() = 0;
};

