#define _USE_MATH_DEFINES
#include <cmath>

#include "pac.h"
#include "gameboard.h"
#include "GL\glut.h"
#include <iostream>

// How far from tile center pacman can change his direction:
static const double CORNERING = 0.3;

Pac::Pac(int tx, int ty) : Creature(tx,ty,0)
{
	z = 0;
	speed = 0.07;
	angle = 0;
	moving = true;

	lives = 3;
}

Pac::~Pac() { }

void Pac::Draw() 
{
	//draw current pacman
	glNormal3f(0.0f, 0.0f, 1.0f);
	glColor3f(1,1,0); // yellow
	glPushMatrix();
		glTranslatef(x,y,0.0);
		glutSolidSphere(0.5,20,20);
	glPopMatrix();
}

// true if COIN was eaten
bool ConsumeMap(int x, int y)
{
	int idx = GameBoard::DIM_Y - y - 1;
	if (GameBoard::initial_map[idx][x] == 0 || GameBoard::initial_map[idx][x] == 5)
	{
		// consume a coin (-1 value indicates eaten)
		GameBoard::initial_map[idx][x] = -1;
		return true;
	} else
	if (GameBoard::initial_map[idx][x] == 3)
	{
		// consume energizer
		GameBoard::initial_map[idx][x] = -1;
	}
	return false;
}

// true if COIN (not energizer) was eaten
bool Pac::Consume()
{


	if (x - (int)x < CORNERING &&  angle == 180) // going left
	{
		if (ConsumeMap((int)x,(int)y))
			return true;
	} else 
	if (x - (int)x >= 1 - CORNERING && angle == 0) // goin right
	{
		if(ConsumeMap((int)x + 1,(int)y))
			return true;
	} else 
	if (y - (int)y < CORNERING && angle == 270) // goin bottom
	{
		if(ConsumeMap((int)x,(int)y))
			return true;
	} else 
	if (y - (int)y >= 1 - CORNERING && angle == 90) // goin top
	{
		if (ConsumeMap((int)x,(int)y + 1))
			return true;
	}
	return false;
}


// helper function
void Pac::PadAndMove(int a)
{
	if (angle != (a + 180) % 360)
	{
		Creature::Pad();
	}
	moving = true;
	angle = a;
}

void Pac::Turn(int nangle) // new angle
{
	//std::cout << "angle " << angle << " New angle " << nangle << std::endl;
	if (angle != nangle) // do not consider the same direction
	{
		if (nangle == 180) // wanting to go left
		{
				y += (1 - (y - (int)y));
				PadAndMove(nangle);

		} else
		if (nangle == 0) // wanting to go right
		{
				y += (1 - (y - (int)y));
				PadAndMove(nangle);

		} else
		if (nangle == 90) // wanting to go top
		{
				x += (1 - (x - (int)x));
				PadAndMove(nangle);

		} else
		if (nangle == 270) // wanting to go bottom
		{ // going from left

				x += (1 - (x - (int)x));
				PadAndMove(nangle);
		}
	}
}


