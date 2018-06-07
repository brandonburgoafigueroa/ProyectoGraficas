#include "creature.h"

class Pac : public Creature {

public:
	double z;
	Pac(int x, int y);
	void Draw();
	void Turn(int v);
	void PadAndMove(int a);
};
