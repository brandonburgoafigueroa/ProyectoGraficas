#define _USE_MATH_DEFINES
#include <cmath>
#include "creature.h"
#include <iostream>

// Difference between current position and the tile center.

Creature::Creature(int x_b, int y_b)
{
	x = x_b;
	y = y_b;

}


// Basic movement algorithm.
void Creature::Move()
{
	x += speed*cos(M_PI/180*angle); // dodawany jakis staly interwal
	y += speed*sin(M_PI/180*angle);
}

