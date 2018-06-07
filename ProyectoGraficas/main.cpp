#define _USE_MATH_DEFINES
#include <cmath>

#include <windows.h>
#include <GL/gl.h>
#include "GL\glut.h"
#include "creature.h"
#include "pac.h"
#include "gameboard.h"
#include "scrnsave.h"
#include <iostream>
#include <string>


GameBoard *board;

Pac *pacman;


GLdouble centerX = GameBoard::CENTER_X;
GLdouble centerY = GameBoard::CENTER_Y;
GLdouble centerZ = GameBoard::CENTER_Z;
GLdouble centerDistance = 15;


GLdouble eyeX = 0;
GLdouble eyeY = 0;
GLdouble eyeZ = 0;


void init()
{   
	glEnable(GL_DEPTH_TEST); 
	glEnable(GL_COLOR_MATERIAL); 

	
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}

void display()
{
	float orthoOffset = 2.0f;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective( 90, 1, 5, 30.0 );

	glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();


	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); 

	eyeX = centerX + 5 * sin(0);
	eyeY = centerY + centerDistance * sin(0) + 5 * sin(0);
	eyeZ = centerZ + centerDistance * cos(0);
	gluLookAt( eyeX, eyeY, eyeZ, centerX, centerY, centerZ, sin(0), cos(0), 0 );

	pacman->Move();	
	board->Draw();
	pacman->Draw();


    glFlush();
	glutSwapBuffers();
}

void special( int key, int x, int y )
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
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); 
	glutInitWindowPosition( 100, 10 );
	glutInitWindowSize( 1000, 1000 );
	glutCreateWindow("PackMan");

	glutDisplayFunc( display );
	glutIdleFunc(display);

	glutSpecialFunc(special);

	
	pacman = new Pac(15,2);
	board = new GameBoard();



	init();

	glutMainLoop(); 

	return 0;
}