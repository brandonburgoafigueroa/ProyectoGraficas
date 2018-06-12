#pragma once
#include <windows.h>
#include "resource.h"
#include "basic_gl_shapes.h"
class Bordes {

public:

	static const int X = 30;
	static const int Y = 15;
	static const int CENTRO_X = X / 2;
	static const int CENTRO_Y = (Y + 1) / 2;
	static const int CENTRO_Z = 0;

	Bordes() {}

	void Dibujar()
	{
		for (int i = 0; i < X; i++)
		{
			for (int j = 0; j < Y; j++)
			{
				DibujarPared(j, i);

			}
		}


	}
	void DibujarBorde(int x, int y, int z)
	{
		glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

		glEnableClientState(GL_COLOR_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		glEnableClientState(GL_VERTEX_ARRAY);

		glNormalPointer(GL_FLOAT, 0, normals);
		glVertexPointer(3, GL_FLOAT, 0, vertices);
		glColorPointer(3, GL_FLOAT, 0, colors);

		glPushMatrix();
		glTranslatef(x, y, z);
		glScalef(0.5, 0.5, 0.2);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, indices);
		glPopMatrix();
	}
	void DibujarPared(int j, int i)
	{
		
		if (j > 0 && j < Y - 1 && i > 0 && i < X - 1)
		{

		}
		else
			DibujarBorde(i, Y - j - 1, CENTRO_Z);

	}

};
