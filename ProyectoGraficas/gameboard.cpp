#include "gameboard.h"
#include "GL\glut.h"
#include <iostream>
#include <vector>
#include "basic_gl_shapes.h"

using namespace std;

// Zmienne do kontroli animacji monet:
int coinAngle = 0;

// 0 - coin
// 1 - wall
// 2 - gate
// 3 - energizer
// 4 - ghost initial positions		

int GameBoard::initial_map[GameBoard::DIM_Y][GameBoard::DIM_X] =
{  //0                   1         5         2                 29
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, // 0
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,1}, // 1
	{1,0,1,0,1,1,1,1,1,1,1,1,0,1,0,1,1,1,0,1,0,1,1,1,0,0,0,1,0,1}, // 2
	{1,3,1,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,1,0,1,0,1,3,1},
	{1,0,1,0,1,1,1,0,1,1,1,1,0,0,0,0,0,1,0,1,1,1,0,0,0,1,0,1,0,1}, // 4

	{1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,1,1,0,0,1,0,1,0,1,0,1}, // 5
	{1,0,1,1,1,1,1,1,1,1,1,1,0,1,0,0,0,0,0,0,1,0,1,1,0,1,0,1,0,1},
	{1,0,0,0,0,0,0,0,0,0,1,1,0,1,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,1,1,1,0,1,1,1,0,1,1,0,1,0,0,0,0,0,0,1,0,1,1,0,1,1,1,1,1},
	{1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,1,1,0,1,0,1,0,0,0,0,0,0,0,0,1},

	{1,1,1,0,1,1,1,0,1,0,1,1,1,1,0,0,0,0,1,0,1,1,0,1,1,1,0,1,0,1}, // 10
	{1,3,0,0,0,0,0,0,0,0,0,0,0,1,0,1,1,0,0,0,0,0,0,0,0,0,0,1,3,1},
	{1,0,1,1,1,1,1,0,1,1,1,1,0,1,0,0,0,0,1,1,1,1,1,0,1,1,1,1,0,1}, // 12
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1}, // 13
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, // 14
};


void GameBoard::TextureLoad(int id)
{
	HBITMAP Bitmap = NULL;
	HINSTANCE myInstance = GetModuleHandle(NULL);

	Bitmap = (HBITMAP)LoadImage(myInstance,MAKEINTRESOURCE(id),IMAGE_BITMAP,0,0, LR_CREATEDIBSECTION);
	GetObject(Bitmap,sizeof(BM),&BM);
	
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); // wiecej pikseli, jak jestesmy blizej obiektu
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // mniej pikseli im dalej

	// glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,BM.bmWidth,BM.bmHeight,0,GL_BGR_EXT,GL_UNSIGNED_BYTE,BM.bmBits);

	DeleteObject((HGDIOBJ) Bitmap);
}

// draw wall with vertex arrays - http://www.songho.ca/opengl/gl_vertexarray.html
void GameBoard::DrawWall(int x, int y, int z)
{
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glTexCoordPointer(2,GL_FLOAT,0,textures);
	glNormalPointer(GL_FLOAT, 0, normals);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
	glColorPointer(3, GL_FLOAT, 0, colors);
	glPushMatrix();
		glTranslatef(x,y,z);
		glScalef(0.5,0.5,0.2);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, indices);
	glPopMatrix();

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);  // disable vertex arrays
    glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);

	glDisable(GL_TEXTURE_2D);
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
			// wall drawing
			DrawWalls(j,i);

		}
	}
}

void GameBoard::DrawWalls(int j, int i)
{
	if (initial_map[j][i] == 1) 
	{ // wall drawing algorithm
		if (j > 0 && j < DIM_Y - 1 && i > 0 && i < DIM_X - 1) 
		{
			int counter = 0;
			int angle = -1;
			if (initial_map[j + 1][i] <= 0)
				counter++;
			else
				angle = 0;
			if (initial_map[j][i + 1] <= 0)
				counter++;
			else
				angle = 90;
			if (initial_map[j - 1][i] <= 0)
				counter++;
			else 
				angle = 180;
			if (initial_map[j][i - 1] <= 0)
				counter++;
			else
				angle = 270;}
			else
				DrawWall(i, DIM_Y - j - 1,CENTER_Z);
		
	}
}

// Perform checking whether there is a wall on specific tile (described as x,y)
bool GameBoard::isWall(int x, int y)
{
	int idx = DIM_Y - y - 1;
	//std::cout << "accessing: " <<  idx << "," << x << ", v: " << walls_map[idx][x] << std::endl;
	return (initial_map[idx][x] == 1 || initial_map[idx][x] == 2);
}
