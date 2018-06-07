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


// board game:
GameBoard *board;

// mr. pacman
Pac *pacman;
bool pacFollowed = false;


// Camera up/down maximums:




// Initial camera looking target
GLdouble centerX = GameBoard::CENTER_X;
GLdouble centerY = GameBoard::CENTER_Y;
GLdouble centerZ = GameBoard::CENTER_Z;
GLdouble centerDistance = 15;

// Camera (i.e. observer) coordinates
GLdouble eyeX = 0;
GLdouble eyeY = 0;
GLdouble eyeZ = 0;


void init()
{   
	glEnable(GL_DEPTH_TEST); // intialization of 3D rendering
	glEnable(GL_COLOR_MATERIAL); // object material properties enabled

	
	glEnable(GL_LIGHTING); // general lighting enabled
	glEnable(GL_LIGHT0);
}

// renderowanie grafiki
void display()
{
	//std::cout << "render" << std::endl;
	float orthoOffset = 2.0f;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// TODO
	//glOrtho(-orthoOffset, GameBoard::DIM_X + orthoOffset, -orthoOffset, GameBoard::DIM_Y + orthoOffset, 0.1, 10 );
	//gluOrtho2D(-orthoOffset, GameBoard::DIM_X + orthoOffset, -orthoOffset, GameBoard::DIM_Y + orthoOffset );
	//glFrustum(-10.25, 10.25, -10.25, 10.25, 1, 1.3);
	gluPerspective( 90, 1, 5, 30.0 ); // 4. parametr - ile widzimy

	glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();


	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // czysc bufory

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
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // pojedyncze buforowanie oraz bufor glebokosci ustawiamy
	glutInitWindowPosition( 100, 10 );
	glutInitWindowSize( 1000, 1000 );
	glutCreateWindow("PackMan");

	glutDisplayFunc( display );
	glutIdleFunc(display);

	glutSpecialFunc(special);

	// OpenGL objects initialization:
	pacman = new Pac(15,2);
	board = new GameBoard();

	// Ghosts initial configuration:


	init();

	glutMainLoop(); // w momencie wywolania nasz program zaczyna dzialac. Reaguje od tego momentu na zdarzenia.

	return 0;
}