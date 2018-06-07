#include "gameboard.h"
#include "GL\glut.h"
#include <iostream>
#include <vector>
#include "basic_gl_shapes.h"

using namespace std;





void GameBoard::DrawWall(int x, int y, int z)
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
		glTranslatef(x,y,z);
		glScalef(0.5,0.5,0.2);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, indices);
	glPopMatrix();

}



GameBoard::GameBoard()
{
}

void GameBoard::Draw()
{	
	for (int i = 0; i < DIM_X; i++)
	{
		for (int j = 0; j < DIM_Y; j++)
		{
			DrawWalls(j,i);

		}
	}
}

void GameBoard::DrawWalls(int j, int i)
{

		if (j > 0 && j < DIM_Y - 1 && i > 0 && i < DIM_X - 1) 
		{
			
		}
			else
				DrawWall(i, DIM_Y - j - 1,CENTER_Z);
		
	
}


