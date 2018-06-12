#define _USE_MATH_DEFINES
#include <cmath>

#include "basic_gl_shapes.h"
#include "Fantasma.h"
#include "Bordes.h"
#include "GL\glut.h"
#include <iostream>
#include <vector>
#include <exception>

static const double CENTER_DIM = 0.05;
Ghost::Ghost(float tr, float tg, float tb, int tx, int ty, float tz)
{
	angle = 180; // initially all ghosts move to the left
	speed = 0.03;
	x = tx;
	y = ty;
	z = tz;
	tileX = tx;
	tileY = ty;

	atCenter = true;
	r = tr;
	g = tg;
	b = tb;

	if (index == 1)
	{
		// red ghost
		scatterTileX = Bordes::CENTRO_X - 2;
		scatterTileY = Bordes::CENTRO_Y + 4;
	}
}

// Ghost appearance.
void Ghost::Draw()
{
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glPushMatrix();
	// overall ghost parameters:
	glTranslatef(x, y, z / 10);
	glColor3f(r, g, b);
	glScalef(0.25, 0.25, 0.05);
	//glRotatef(phi * 90,0,sin(phi),cos(phi)); // fix this
	glPushMatrix();
	glScalef(0.2, 0.2, 1);
	glPushMatrix(); // solid body
	glPushMatrix();
	glScalef(2, 0.5, 1);
	glTranslatef(0, 17, 0);
	Block();
	glPopMatrix();
	glPushMatrix();
	glScalef(4, 1, 1);
	glTranslatef(0, 7, 0);
	Block();
	glPopMatrix();
	glPushMatrix();
	glScalef(6, 1.5, 1);
	glTranslatef(0, 3, 0);
	Block();
	glPopMatrix();
	glPushMatrix();
	glScalef(7, 3, 1);
	Block();
	glPopMatrix();
	glPopMatrix();
	glPushMatrix(); // details
	glPushMatrix(); // top details
	glTranslatef(4.5, 6.5, 0);
	glScalef(0.5, 0.5, 1);
	Block();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-4.5, 6.5, 0);
	glScalef(0.5, 0.5, 1);
	Block();
	glPopMatrix();
	glPushMatrix(); // bot detals
	glTranslatef(2, -4, 0);
	glScalef(1, 1, 1);
	Block();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-2, -4, 0);
	glScalef(1, 1, 1);
	Block();
	glPopMatrix();
	glPushMatrix(); // bot details 2
	glTranslatef(3.5, -3.5, 0);
	glScalef(0.5, 0.5, 1);
	Block();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-3.5, -3.5, 0);
	glScalef(0.5, 0.5, 1);
	Block();
	glPopMatrix();
	glPushMatrix(); // bot details 3
	glTranslatef(6, -3.5, 0);
	glScalef(1, 0.5, 1);
	Block();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-6, -3.5, 0);
	glScalef(1, 0.5, 1);
	Block();
	glPopMatrix();
	glPushMatrix(); // bot details 4
	glTranslatef(6.5, -4.5, 0);
	glScalef(0.5, 0.5, 1);
	Block();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-6.5, -4.5, 0);
	glScalef(0.5, 0.5, 1);
	Block();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
}

void Ghost::calcCurrentTile()
{
	if ((angle == 0) && (x - (int)x > 0.5))
		tileX = (int)ceil(x);
	if ((angle == 180) && (x - (int)x < 0.5))
		tileX = (int)floor(x);
	if ((angle == 90) && (y - (int)y > 0.5))
		tileY = (int)ceil(y);
	if ((angle == 270) && (y - (int)y < 0.5))
		tileY = (int)floor(y);
}

bool Ghost::isCenterTile()
{
	return (
		((angle == 0) && (x - (int)x > 1 - CENTER_DIM)) ||
		((angle == 180) && (x - (int)x < CENTER_DIM)) ||
		((angle == 90) && (y - (int)y > 1 - CENTER_DIM)) ||
		((angle == 270) && (y - (int)y < CENTER_DIM))) ? true : false;
}

// Basic movement algorithm.
void Ghost::Move()
{
	if (moving)
	{
		x += speed * cos(M_PI / 180 * angle); // dodawany jakis staly interwal
		y += speed * sin(M_PI / 180 * angle);

		if (!atCenter && isCenterTile())
		{
			atCenter = true;
			//onTileCenter();
		}
	}

	int oldTileX = tileX;
	int oldTileY = tileY;

	calcCurrentTile();

	if (tileX != oldTileX || tileY != oldTileY) // kiedy wszedlem na nowa plytke
	{
		atCenter = false;  // wtedy moge szukac centrum nowej plytki
						   //onTileChange();
	}
}

void Ghost::Pad()
{
	x = (int)x;
	y = (int)y;
}

void Ghost::PadToCenter()
{
	x = tileX;
	y = tileY;
}
