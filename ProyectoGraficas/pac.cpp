#include "pac.h"
#include "GL\glut.h"
#include <iostream>

Pac::Pac(int tx, int ty) : Creature(tx,ty,0)
{
	z = 0;
	speed = 0.09;
	angle = 0;
}


void Pac::Draw() 
{
	glColor3f(1,1,0);
	glPushMatrix();
		glTranslatef(x,y,0.0);
		glutSolidSphere(2,400,400);
	glPopMatrix();
}


void Pac::PadAndMove(int a)
{
	angle = a;
}

void Pac::Turn(int nangle)
{

		if (nangle == 180)
		{
				PadAndMove(nangle);
		} else
		if (nangle == 0)
		{
				PadAndMove(nangle);

		} else
		if (nangle == 90)
		{
				PadAndMove(nangle);

		} else
		if (nangle == 270)
		{
				PadAndMove(nangle);
		}
	
}


