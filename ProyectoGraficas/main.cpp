#pragma once

#include <windows.h>
#include <GL/gl.h>
#include "GL\glut.h"
#include "Pacman.h"
#include "Bordes.h"
#include <iostream>
#include <string>
#include "Fantasma.h"
Bordes *board;

Pacman *pacman;

Ghost *fantasma;

float ghostsColors[] = { 1.0, 0.0,   0.0,   // Blinky
1.0, 0.753, 0.796, // Pinky
0.0, 1.0,   1.0,   // Inky
1.0, 0.647, 0.0  // Clyde
};



GLdouble centerX = Bordes::CENTRO_X;
GLdouble centerY = Bordes::CENTRO_Y;
GLdouble centerZ = Bordes::CENTRO_Z;


GLdouble eyeX = 0;
GLdouble eyeY = 0;
GLdouble eyeZ = 0;


void Inicializar()
{   
	glEnable(GL_DEPTH_TEST); 
	glEnable(GL_COLOR_MATERIAL); 

	
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}

void Mostrar()
{	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective( 90, 1, 5, 30.0 );

	glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();


	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); 

	eyeX = centerX;
	eyeY = centerY;
	eyeZ = centerZ + 15;
	gluLookAt( eyeX, eyeY, eyeZ, centerX, centerY, centerZ, 0, 1, 0 );
	pacman->Move();	
	board->Dibujar();
	pacman->Draw();
	fantasma->Move(pacman);
	fantasma->Draw();
    glFlush();
	glutSwapBuffers();
}

void Teclado( int key, int x, int y )
{
	switch( key )
    {
	case GLUT_KEY_LEFT:
		pacman->Turn(180);
        break;

    case GLUT_KEY_RIGHT:   
		pacman->Turn(0);
        break;

    case GLUT_KEY_UP:
		pacman->Turn(90);
        break;
       
    case GLUT_KEY_DOWN:
		pacman->Turn(270);
        break;
    }

}


int main(int argc, char** argv)
{
	glutInit( &argc, argv );
	glutInitWindowPosition( 100, 10 );
	glutInitWindowSize( 1000, 1000 );
	glutCreateWindow("Pacman Farol");

	glutDisplayFunc( Mostrar );
	glutIdleFunc(Mostrar);

	glutSpecialFunc(Teclado);

	
	pacman = new Pacman(15,2);
	fantasma = new Ghost(ghostsColors[3 * 0], ghostsColors[3 * 0 + 1], ghostsColors[3 * 0 + 2], 13 + 0, 10, 2);
	board = new Bordes();

	Inicializar();

	glutMainLoop(); 

	return 0;
}