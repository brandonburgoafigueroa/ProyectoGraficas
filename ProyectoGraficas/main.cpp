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

// basic game information
std::string infoText[] = 
{
	"Coins left: ",
	"Lives: "
};

// zooming - max Z distance and min Z distance
float maxZ = 15;
float minZ = 8;

// Camera up/down maximums:
float camUpDownMax = 0.8;

// Camera left/right maximums:
float camLRMax = 0.8;

// Camera rotation angles:
double theta = 0;
double phi = 0;

// Initial camera looking target
GLdouble centerX = GameBoard::CENTER_X;
GLdouble centerY = GameBoard::CENTER_Y;
GLdouble centerZ = GameBoard::CENTER_Z;
GLdouble centerDistance = 15;

// Camera (i.e. observer) coordinates
GLdouble eyeX = 0;
GLdouble eyeY = 0;
GLdouble eyeZ = 0;

// Lighting:
float lightIntensity = 1;

void init()
{   
	// ustaw intensywnosc swaitla i kolor
	// https://www.youtube.com/watch?v=g_0yV7jZvGg
	// https://www.youtube.com/watch?v=gFZqzVQrw84 // swietny opis rodzajow swiatel
	// https://www.youtube.com/watch?v=oVwH8KV1xnY // najlepsze

	// General OpenGL configirations:
	glEnable(GL_DEPTH_TEST); // intialization of 3D rendering
	glEnable(GL_COLOR_MATERIAL); // object material properties enabled
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE); // set material properties which will be assigned by glColor
	glEnable(GL_NORMALIZE); // Automatically normalize normals (vectors of surfaces )
	
	glEnable(GL_LIGHTING); // general lighting enabled
	glEnable(GL_LIGHT0);
	
	// Create light components
	GLfloat ambientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	GLfloat diffuseLight[] = { 0.8f, 0.8f, 0.8, 1.0f };
	GLfloat specularLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat position[] = { GameBoard::CENTER_X, GameBoard::CENTER_Y, 4.0f, 1.0f };
 
	// Assign created components to GL_LIGHT0
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
	glLightfv(GL_LIGHT0, GL_POSITION, position);

	//glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.0);
	//glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.6);
	//glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.5);

	// Add global ambient light
    //GLfloat ambientColor[] = { 0.5, 0.5,  0.5, 1.0 };
	//glLightModelfv( GL_LIGHT_MODEL_AMBIENT, ambientColor); // ambient lights everywhere with the same amount 
   
	GLfloat mat_ambient[]  = { 1.0, 1.0,  1.0, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0,  1.0, 1.0 };

	//glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient );
    //glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular );
    //glMaterialf( GL_FRONT_AND_BACK, GL_SHININESS, 10.0 );

	glShadeModel(GL_SMOOTH); // smooth shading
    glDepthFunc( GL_LESS );
}

void DrawInfo() 
{
	// buffer for storing coinsCount
	static const int buf_length = 4;
	static char count_buffer[buf_length];
	std::printf(count_buffer,"%d",pacman->lives);
	std::printf(count_buffer + 1,"%d",board->coinsCount); // very unsafe! Be careful!

	// updating coins count
	// http://stackoverflow.com/questions/18847109/displaying-fixed-location-2d-text-in-a-3d-opengl-world-using-glut
	glDisable(GL_TEXTURE_2D);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0,500,0,500);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
		glLoadIdentity();
		glColor3d(1.0, 1.0, 1.0);
		//std::cout << static_cast <char>(board->coinsCount) << std::endl;
		// text display functionality			
		for (int i = 0; i < sizeof(infoText) / sizeof(infoText[0]); i++)
		{
			glRasterPos2i(10, 500 - 20 - i * 18); // initial position of a raster.
			for (std::string::iterator j = infoText[i].begin(); j != infoText[i].end(); ++j)
			{
				glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,*j);
			}
			if (i == 0)
			{ // display coinsCount
				for (int j = 1; j < buf_length; j++)
				{
					glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, count_buffer[j]);
				}
			}
			if (i == 1)
			{ // display lives
				glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, count_buffer[0]);
			}
		}
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	//added this
	glEnable(GL_TEXTURE_2D);
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

	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // czysc bufory

	// lighting stuff:
	glPushMatrix();
		GLfloat lightPos0[] = { pacman->x, pacman->y, 4.0f, 1.0f };
		glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
	glPopMatrix();

	// camera movement stuff:
	// http://gamedev.stackexchange.com/questions/43588/how-to-rotate-camera-centered-around-the-cameras-position
	// M_PI /2 - przesuniecie fazowe w celu dobrego wyswietlenia poczatkowego planszy
	// implementacja operacji: ROLL (theta) (zla!) oraz PITCH (phi) ('w', 's' jest ok)
	if (pacFollowed) 
	{ // look at pacman 
		centerX = pacman->x;
		centerY = pacman->y;
		centerZ = pacman->z;
	}
	else 
	{ // look at the middle of the gameboard
		centerX = GameBoard::CENTER_X;
		centerY = GameBoard::CENTER_Y;
		centerZ = GameBoard::CENTER_Z;
	}

	eyeX = centerX + 5 * sin(theta);
	eyeY = centerY + centerDistance * sin(phi) + 5 * sin(theta);
	eyeZ = centerZ + centerDistance * cos(phi);
	gluLookAt( eyeX, eyeY, eyeZ, centerX, centerY, centerZ, sin(theta), cos(theta), 0 );


	// move the pacman
	pacman->Move();	

	// wall check stops movement
	pacman->WallCheck();

	// coins eating
	if (pacman->Consume())
		board->coinsCount--;

	// ghosts movement algorithms:
	// Blinky:
	

	// actual pacman, ghosts and board drawing
	board->Draw();
	pacman->Draw();

	// screen information
	DrawInfo();

    glFlush(); // wyczysc wszystkie bufory. Standard zaleca wywolywanie tej komendy.
	glutSwapBuffers();
}


void reshape(GLsizei w, GLsizei h)
{
    glViewport( 0, 0, w, h );
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
	        
	GLdouble aspect = w /( GLdouble ) h;
   
    // rzutowanie perspektywiczne
	gluPerspective( 90, 1, 5, 30.0 );
}

void keyboard(unsigned char key, int x, int y)
{
	static float step = 0.1;
	static float stepZoom = 1;

	// Camera / zooming
	switch (key)
	{
	case 'a':
		// left
		if (theta < -camLRMax)
			return;
		theta -= step;
		break;
       
	case 'w':
		// up
		if (phi > camUpDownMax)
			return;
		phi += step;
		break;
       
	case 'd':     
		// right
		if (theta > camLRMax)
			return;
		theta += step;
		break;
       
	case 's':
		// down
		if (phi < -camUpDownMax)
			return;
		phi -= step;
		break;

	case 'r':
		// zoom in
		if (centerDistance < minZ)
			return;
		centerDistance -= stepZoom;
		//positionz += stepZoom;
		break;

	case 'f':
		// zoom out
		if (centerDistance > maxZ)
			return;
		centerDistance += stepZoom;
		//positionz -= stepZoom;
		break;

	case 'c':
		//follow camera mode
		pacFollowed = pacFollowed ? false : true;
		pacFollowed ? centerDistance = maxZ - 4 : centerDistance = maxZ;
		if(!pacFollowed)
		{
			// reset angles when returning from following mode
			phi = 0;
			theta = 0;
		}
		break;

	case 't':
			
	break;

	case 'g':

	break;
	}
}

// Mouse handling
void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_RIGHT_BUTTON) {
		exit(0);
	}
}

// Special keys handling (arrows)
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

	// odrysowanie okna
    reshape( glutGet( GLUT_WINDOW_WIDTH ), glutGet( GLUT_WINDOW_HEIGHT ) );
}

void timer(int v) 
{
	// maybe some visual effects?
}

int main(int argc, char** argv)
{
	glutInit( &argc, argv );
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // pojedyncze buforowanie oraz bufor glebokosci ustawiamy
	glutInitWindowPosition( 100, 10 );
	glutInitWindowSize( 1000, 1000 );
	glutCreateWindow( "PackMan" ); // zainicjowany kontekst openGL'owy

	//glutGameModeString( "800x600:16@60" );
	//glutEnterGameMode();

	glutSetCursor(GLUT_CURSOR_NONE);

	glutDisplayFunc( display );
	glutReshapeFunc( reshape ); // trzeba zmienic parametry rzutowania
	glutIdleFunc(display); // scena jest caly czas przeliczana w tle

	glutTimerFunc(40, timer, 1);

	glutSpecialFunc(special);
	glutKeyboardFunc(keyboard);

	// OpenGL objects initialization:
	pacman = new Pac(15,2);
	board = new GameBoard();

	// Ghosts initial configuration:


	init();

	glutMainLoop(); // w momencie wywolania nasz program zaczyna dzialac. Reaguje od tego momentu na zdarzenia.

	return 0;
}