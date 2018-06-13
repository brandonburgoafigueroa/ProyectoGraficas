#pragma once
#include "GL\glut.h"
#include "Pacman.h"
#include "basic_gl_shapes.h"
class Fantasma {

public:
	float r;
	float g;
	float b;
	float x, y, z;
	double speed;
public:

	Fantasma(float r, float g, float b, int x, int y, float z)
	{
		speed = 0.001;
		this->x = x;
		this->y = y;
		this->z = z;
		this->r = r;
		this->g = g;
		this->b = b;
	}

	void Move(Pacman *pacman)
	{

		if (pacman->top || pacman->down)
		{
			if (y < pacman->y)
			{
				y = y + y * speed;
			}
			else
			{
				y = y - y * speed;
			}
		}
		if (pacman->left || pacman->right)
		{
			if (x < pacman->x)
			{
				x = x + x * speed;
			}
			else
			{
				x = x - x * speed;
			}
		}
	}


	void Draw()
	{
		glEnableClientState(GL_NORMAL_ARRAY);
		glEnableClientState(GL_VERTEX_ARRAY);
		glPushMatrix();
		glTranslatef(x, y, z / 10);
		glColor3f(r, g, b);
		glScalef(0.5, 0.5, 0.5);

		glPushMatrix();
		glScalef(0.2, 0.2, 1);
		glPushMatrix();
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
		glPushMatrix();
		glPushMatrix();
		glTranslatef(4.5, 6.5, 0);
		glScalef(0.5, 0.5, 1);
		Block();

		glPopMatrix();
		glPushMatrix();
		glTranslatef(-4.5, 6.5, 0);
		glScalef(0.5, 0.5, 1);
		Block();
		glPopMatrix();
		glPushMatrix();
		glTranslatef(2, -4, 0);
		glScalef(1, 1, 1);
		Block();
		glPopMatrix();
		glPushMatrix();
		glTranslatef(-2, -4, 0);
		glScalef(1, 1, 1);
		Block();
		glPopMatrix();
		glPushMatrix();
		glTranslatef(3.5, -3.5, 0);
		glScalef(0.5, 0.5, 1);
		Block();
		glPopMatrix();
		glPushMatrix();
		glTranslatef(-3.5, -3.5, 0);
		glScalef(0.5, 0.5, 1);
		Block();
		glPopMatrix();
		glPushMatrix();
		glTranslatef(6, -3.5, 0);
		glScalef(1, 0.5, 1);
		Block();
		glPopMatrix();
		glPushMatrix();
		glTranslatef(-6, -3.5, 0);
		glScalef(1, 0.5, 1);
		Block();
		glPopMatrix();
		glPushMatrix();
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
	

};
